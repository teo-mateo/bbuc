using Accord.Imaging.Filters;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BaroulBucuresti.Vot.Detection;
using Accord.Imaging;
using Accord.Math.Geometry;
using Accord;
using System.Windows;
using System.Diagnostics;
using Ghostscript.NET.Rasterizer;

namespace BaroulBucuresti.Vot.models
{
    public class VotVM
    {
        public string Filename {get;set;}
        public bool Processed { get; set; }
        public bool Nullified { get; set; }
        public bool Manual { get; set; }

        public VotVM(string fn, bool p, bool n, bool m)
        {
            Filename = fn;
            Processed = p;
            Nullified = n;
            Manual = m;
        }
    }

    public class Vot : INotifyPropertyChanged
    {
        System.Drawing.Rectangle RectLeft { get; set; }
        System.Drawing.Rectangle RectRight { get; set; }
        List<Rectangle> LeftBoxes = new List<Rectangle>();
        List<Rectangle> RightBoxes = new List<Rectangle>();

        private void OnPropertyChanged(string name)
        {
            var handler = PropertyChanged;
            if (handler != null)
                handler(this, new PropertyChangedEventArgs(name));
        }
        public event PropertyChangedEventHandler PropertyChanged;

        public Vot() { }

        

        public Vot(string filename)
        {
            _filename = filename;
            _result = new bool[App.OptiuniVot.Count];

            //LoadImageBitmap();

            
        }

        private System.Drawing.Bitmap _bitmap;
        private System.Drawing.Bitmap _wBitmap;

        public void LoadImageBitmap()
        {
            try {
                if (_bitmap != null) {
                    _bitmap.Dispose();
                    _bitmap = null;
                }

                if (_wBitmap != null) {
                    _wBitmap.Dispose();
                    _wBitmap = null;
                }

                if (!System.IO.File.Exists(_filename)) {
                    return;
                }

                int desired_x_dpi = 200;
                int desired_y_dpi = 200;

                using (var rasterizer = new GhostscriptRasterizer()) {
                    rasterizer.Open(_filename);

                    if (rasterizer.PageCount > 1) {
                        return;
                    }

                    for (var pageNumber = 1; pageNumber <= rasterizer.PageCount; pageNumber++) {
                        var img = rasterizer.GetPage(desired_x_dpi, desired_y_dpi, pageNumber);
                        _bitmap = (System.Drawing.Bitmap)img;
                    }
                }


            }
            catch(Exception ex) {
                Manual = true;
            }
        }

        private Bitmap GetWorkingBitmap()
        {
            Bitmap temp = Accord.Imaging.Image.Clone(_bitmap, PixelFormat.Format24bppRgb);
            // get grayscale image
            return Grayscale.CommonAlgorithms.RMY.Apply(temp);
        }

        public System.Drawing.Bitmap ShowBitmap {
            get {
                return _bitmap;
            }
        }


        public System.Drawing.Bitmap DisplayBitmap {
            get {
                return _bitmap;
            }
        }


        public void ApplyCannyFilter(byte low, byte high, double sigma)
        {

            var f = new SobelEdgeDetector();

            _wBitmap = GetWorkingBitmap();

            var filter = new CannyEdgeDetector(low, high, sigma);
            _wBitmap = filter.Apply(_wBitmap);
            OnPropertyChanged("ShowBitmap");
        }

        public long Id { get; set; }

        public VotVM VotVM {
            get {
                return new VotVM(ShortFilename, Processed, Nullified, Manual);
            }
        }

        private string _filename;
        public string FileName {
            get { return _filename; }
            set {
                _filename = value;
                Save();
                OnPropertyChanged("VotVM");
            }
        }

        public string ShortFilename {
            get {
                if (!string.IsNullOrEmpty(_filename)) {
                    return _filename.Substring(_filename.LastIndexOf("\\") + 1);
                } else {
                    return "???";
                }
            }
        }

        private bool _processed;
        public bool Processed {
            get { return _processed; }
            set {
                _processed = value;
                Save();
                OnPropertyChanged("VotVM");
            }
        }

        private bool _nullified;
        public bool Nullified {
            get { return _nullified; }
            set {
                _nullified = value;
                Save();
                OnPropertyChanged("VotVM");
            }
        }

        private bool _manual;
        public bool Manual {
            get { return _manual; }
            set {
                _manual = value;
                Save();
                OnPropertyChanged("VotVM");
            }
        }

        private bool[] _result;
        public bool[] Result {
            get { return _result; }
            set {
                _result = value;
                Save();
                OnPropertyChanged("VotVM");
            }
        }

        public void Save()
        {
            int processed = Processed ? 1 : 0;
            int nullified = Nullified ? 1 : 0;
            int manual = Manual ? 1 : 0;
            StringBuilder result = new StringBuilder();
            for (int i = 0; i < Result.Length; i++) {
                result.Append(Result[i] ? "1" : "0");
            }

            if (Id == 0) {
                // save new
                var command = String.Format("insert into Votes (filename, processed, nullified, manual, result) values ('{0}', {1}, {2}, {3}, '{4}')", FileName, processed, nullified, manual, result.ToString());
                Database.ExecuteNonQuery(command);

                Id = (long)Database.ExecuteScalar("SELECT last_insert_rowid()");

            } else {
                //update
                var command = String.Format("update Votes set filename='{0}', processed={1} nullified={2}, manual={3}, result='{4}' where id={5}", FileName, processed, nullified, manual, result.ToString(), Id);
                Database.ExecuteNonQuery(command);
            }
        }


        public void Update(string filename=null, bool? processed=null, bool? nullified=null, bool? manual=null, bool[] result=null)
        {
            if (filename != null) {
                _filename = filename;
            }

            if (processed.HasValue) {
                _processed = processed.Value; 
            }

            if (nullified.HasValue) {
                _nullified = nullified.Value;
            }

            if (manual.HasValue) {
                _manual = manual.Value;
            }

            if (result != null) {
                _result = result;
            }

            Save();
        }

        private void SobelEdgeDetection()
        {

        }

        internal bool DetectionStep(Step step)
        {
            switch (step.Type) {
                case StepType.Sharpen:
                    new Sharpen().ApplyInPlace(_wBitmap);
                    _bitmap = Accord.Imaging.Image.Clone(_wBitmap, PixelFormat.Format24bppRgb);
                    return true;
                case StepType.CannyFilter:
                    new CannyEdgeDetector(0, 30, 0.2).ApplyInPlace(_wBitmap);
                    _bitmap = Accord.Imaging.Image.Clone(_wBitmap, PixelFormat.Format24bppRgb);
                    return true;
                case StepType.SobelEdgeDetection:
                    new SobelEdgeDetector().ApplyInPlace(_wBitmap);
                    _bitmap = Accord.Imaging.Image.Clone(_wBitmap, PixelFormat.Format24bppRgb);
                    return true;
                case StepType.DifferenceEdgeDetection:
                    new DifferenceEdgeDetector().ApplyInPlace(_wBitmap);
                    _bitmap = Accord.Imaging.Image.Clone(_wBitmap, PixelFormat.Format24bppRgb);
                    return true;
                case StepType.Median:
                    new Median().ApplyInPlace(_wBitmap);
                    _bitmap = Accord.Imaging.Image.Clone(_wBitmap, PixelFormat.Format24bppRgb);
                    break;
                case StepType.BlobCounter:
                    return BlobCounter();
                case StepType.HoughLines:
                    HoughLines();
                    break;
                case StepType.VoteCounter:
                    return VoteCounter();
            }


            return true;
            OnPropertyChanged("ShowBitmap");
        }

        private bool VoteCounter()
        {
            var rowsCount = App.OptiuniVot.Count / 2 + App.OptiuniVot.Count % 2;

            Rectangle l = new Rectangle(), r = new Rectangle();

            for (int i = 0; i < rowsCount; i++) {

                int yadd = (i % 4 == 0) ? 1 : 0;

                if (i == 0) {
                    l = new Rectangle(RectLeft.Left + 6, RectLeft.Top + 3 + i * (RectLeft.Height / rowsCount), RectLeft.Width - 9, RectLeft.Height / rowsCount - 5);
                    r = new Rectangle(RectRight.Left + 6, RectRight.Top + 3 + i * (RectRight.Height / rowsCount), RectRight.Width - 9, RectRight.Height / rowsCount - 5);
                } else {
                    l = new Rectangle(l.X, l.Y + l.Height + 5+yadd, l.Width, l.Height);
                    r = new Rectangle(r.X, r.Y + r.Height + 5+yadd, r.Width, r.Height);
                }


                LeftBoxes.Add(l);
                RightBoxes.Add(r);
            }


            using (var g = Graphics.FromImage(_bitmap))
            using (Pen pen = new Pen(Color.Yellow, 2)) {

                foreach (var lb in LeftBoxes) {
                    PaintBox(g, pen, lb);
                }

                foreach (var rb in RightBoxes) {
                    PaintBox(g, pen, rb);
                }
            }

            

            return true;
        }

        private void PaintBox(Graphics g, Pen pen, Rectangle r)
        {
            int red = 0, green = 0, blue = 0, alpha = 0;

            for (int i = 0; i < r.Width; i++) {
                for (int j = 0; j < r.Height; j++) {
                    var pixel = _bitmap.GetPixel(r.X + i, r.Y + j);
                    red += pixel.R;
                    green += pixel.G;
                    blue += pixel.B;
                    alpha += pixel.A;
                }
            }

            Func<int, int> avg = c => c / (r.Width * r.Height);

            red = avg(red);
            green = avg(green);
            blue = avg(blue);
            alpha = avg(alpha);

            var color = Color.FromArgb(alpha, red, green, blue);
            System.Diagnostics.Debug.WriteLine("{0}  {1}  {2}  {3}", alpha, red, green, blue);

            if ((red+green+blue) / 3 > 50) {
                color = Color.White;
            }

            g.DrawRectangle(pen, r);
            System.Drawing.Brush b = new System.Drawing.SolidBrush(color);
            g.FillRectangle(b, Rectangle.FromLTRB(r.Left+50, r.Top, r.Right+50, r.Bottom));
            b.Dispose();
        }

        private bool BlobCounter()
        {

            var bitmap = Accord.Imaging.Image.Clone(_wBitmap, PixelFormat.Format24bppRgb);
            // lock image
            BitmapData bitmapData = bitmap.LockBits(ImageLockMode.ReadWrite);

            // step 1 - turn background to black
            ColorFiltering colorFilter = new ColorFiltering();

            colorFilter.Red = new IntRange(0, 64);
            colorFilter.Green = new IntRange(0, 64);
            colorFilter.Blue = new IntRange(0, 64);
            colorFilter.FillOutsideRange = false;

            colorFilter.ApplyInPlace(bitmapData);

            // step 2 - locating objects
            BlobCounter blobCounter = new BlobCounter();
            blobCounter.FilterBlobs = true;
            blobCounter.MinHeight = 100;


            blobCounter.ProcessImage(bitmapData);
            Blob[] blobs = blobCounter.GetObjectsInformation();
            bitmap.UnlockBits(bitmapData);

            // step 3 - check objects' type and highlight
            SimpleShapeChecker shapeChecker = new SimpleShapeChecker();

            using (var g = Graphics.FromImage(_bitmap))
            using (Pen pen = new Pen(Color.Red, 2)) {

                for (int i = 0; i < blobs.Length; i++) {

                    Debug.WriteLine(String.Format("Blob {0}: W: {1}   H:{2}   ", i, blobs[i].Rectangle.Width, blobs[i].Rectangle.Height));

                    List<IntPoint> edgePoints = blobCounter.GetBlobsEdgePoints(blobs[i]);
                    List<IntPoint> corners;

                    if (shapeChecker.IsConvexPolygon(edgePoints, out corners)) {
                        pen.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
                        g.DrawRectangle(pen, blobs[i].Rectangle);
                    }
                }

            }

            RectRight = new Rectangle();
            RectLeft = new Rectangle();

            if (blobs.Length != 2 || blobs.Any(b=>b.Rectangle.Width > 47)) {
                return false;
            }
            else {

                RectLeft = blobs.First().Rectangle;
                RectRight = blobs.Last().Rectangle;
                return true;
            }
        }

        private void HoughLines()
        {
            var image = Accord.Imaging.Image.Clone(_wBitmap, PixelFormat.Format24bppRgb);
            int imageWidth = image.Width;
            int imageHeight = image.Height;

            FiltersSequence filter = new FiltersSequence(Grayscale.CommonAlgorithms.BT709, new Threshold(64));

            HoughLineTransformation lineTransform = new HoughLineTransformation();

            // lock the source image
            BitmapData sourceData = image.LockBits(
                new Rectangle(0, 0, image.Width, image.Height),
                ImageLockMode.ReadOnly, image.PixelFormat);

            // binarize the image
            UnmanagedImage binarySource = filter.Apply(new UnmanagedImage(sourceData));

            // apply Hough line transform
            lineTransform.ProcessImage(binarySource);

            // get lines using relative intensity
            HoughLine[] lines = lineTransform.GetLinesByRelativeIntensity(0.5);






            List<ABLine> ablines = new List<ABLine>();

            foreach (HoughLine line in lines) {

                string s = string.Format("Theta = {0}, R = {1}, I = {2} ({3})", line.Theta, line.Radius, line.Intensity, line.RelativeIntensity);
                System.Diagnostics.Debug.WriteLine(s);

                // uncomment to highlight detected lines

                // get line's radius and theta values
                int r = line.Radius;
                double t = line.Theta;

                // check if line is in lower part of the image
                if (r < 0) {
                    t += 180;
                    r = -r;
                }

                // convert degrees to radians
                t = (t / 180) * Math.PI;

                // get image centers (all coordinate are measured relative
                // to center)
                int w2 = image.Width / 2;
                int h2 = image.Height / 2;

                double x0 = 0, x1 = 0, y0 = 0, y1 = 0;

                if (line.Theta != 0) {
                    // none vertical line
                    x0 = -w2; // most left point
                    x1 = w2;  // most right point

                    // calculate corresponding y values
                    y0 = (-Math.Cos(t) * x0 + r) / Math.Sin(t);
                    y1 = (-Math.Cos(t) * x1 + r) / Math.Sin(t);
                } else {
                    // vertical line
                    x0 = line.Radius;
                    x1 = line.Radius;

                    y0 = h2;
                    y1 = -h2;
                }

                ablines.Add(new ABLine() { P1 = new System.Drawing.Point((int)x0 + w2, h2 - (int)y0), P2 = new System.Drawing.Point((int)x1 + w2, h2 - (int)y1) });
            }

            using (var g = Graphics.FromImage(_bitmap))
            using (Pen pen = new Pen(Color.Red)) {

                pen.Width = 2;

                foreach (var l in ablines) {

                    if (Math.Abs(l.P1.X - l.P2.X) > 200) {
                        continue;
                    }

                    g.DrawLine(pen, l.P1, l.P2);
                }
            }
        }

        public void Detect()
        {
            if (_wBitmap == null) {
                _wBitmap = GetWorkingBitmap();
            }

            List<Step> steps = new List<Step>();
            steps.Add(new Step() { Type = StepType.Median });
            steps.Add(new Step() { Type = StepType.Sharpen });
            steps.Add(new Step() { Type = StepType.DifferenceEdgeDetection });
            steps.Add(new Step() { Type = StepType.BlobCounter });
            steps.Add(new Step() { Type = StepType.VoteCounter });
            bool ok = true;
            foreach(var s in steps) {
                ok = DetectionStep(s);
                if (!ok) {
                    break;
                }
            }

            Processed = ok;
            Manual = !ok;

            _wBitmap.Dispose();
        }
    }
}
