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
    public class VotVM : INotifyPropertyChanged
    {
        public int Index { get; set; }
        public int NrCrt { get; set; }
        public string Candidat { get; set; }
        private bool _optiune; 
        public bool Optiune {
            get {
                return _optiune;
            }
            set {
                _optiune = value;
                OnPropertyChanged("Optiune");
            }
        }

        private void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
        public event PropertyChangedEventHandler PropertyChanged;
    }

    public class BuletinVotVM
    {
        public string Filename {get;set;}
        public bool Processed { get; set; }
        public bool Nullified { get; set; }
        public bool Manual { get; set; }

        public BuletinVotVM(string fn, bool p, bool n, bool m)
        {
            Filename = fn;
            Processed = p;
            Nullified = n;
            Manual = m;
        }
    }

    public class BuletinVot : INotifyPropertyChanged
    {
        private string _processedFN;
        public string ProcessedFN {
            get {
                return _processedFN;
            }
        }

        public List<VotVM> Votes { get; set; }
        public int TotalVoturi {
            get {
                return Votes.Count(v => v.Optiune == true);
            }
        }

        private void SetVotes(Dictionary<int, bool> votes)
        {
            Votes = new List<models.VotVM>();

            var optiuniList = new List<string>();
            for (int i = 0; i < App.OptiuniVot.Count; i++) {
                optiuniList.Add((string)App.OptiuniVot[i].Name);
            }

            for (int i = 0; i < optiuniList.Count; i++) {
                bool optiune = false;
                if (votes != null && votes.ContainsKey(i)) {
                    optiune = votes[i];
                }

                Votes.Add(new VotVM() { Index = i, NrCrt = i + 1, Candidat = optiuniList[i], Optiune = optiune });
                Votes.Last().PropertyChanged += (s, e) => {
                    OnPropertyChanged("TotalVoturi");

                    Result = Votes.OrderBy(v => v.NrCrt).Select(p => p.Optiune).ToArray();
                };
            }



            OnPropertyChanged("Votes");
            OnPropertyChanged("TotalVoturi");
        }

        System.Drawing.Rectangle RectLeft { get; set; }
        System.Drawing.Rectangle RectRight { get; set; }
        List<Rectangle> LeftBoxes = new List<Rectangle>();
        List<Rectangle> RightBoxes = new List<Rectangle>();

        private void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
        public event PropertyChangedEventHandler PropertyChanged;

        public BuletinVot()
        {
            SetVotes(null);
        }

        

        public BuletinVot(string filename)
        {
            _filename = filename;
            _result = new bool[App.OptiuniVot.Count];
            SetVotes(null);
        }

        public BuletinVot(dynamic record)
        {
            _filename = record.filename;
            Id = record.id;
            _processed = (record.processed == 1);
            _nullified = (record.nullified == 1);
            _manual = (record.manual ==  1);
            _result = new bool[App.OptiuniVot.Count];

            var ca = ((string)record.result).ToCharArray();
            Dictionary<int, bool> votes = new Dictionary<int, bool>();
            for (int i = 0; i < ca.Length; i++) {
                _result[i] = (ca[i] == '1');
                votes[i] = (ca[i] == '1');
            }

            SetVotes(votes);
        }

        private System.Drawing.Bitmap _bitmap;

        public void Free()
        {
            if (_bitmap != null) {
                _bitmap.Dispose();
                _bitmap = null;
            }
        }


        public void LoadImageBitmap()
        {
            Stopwatch sw = new Stopwatch();
            sw.Start();

            try {
                if (_bitmap != null) {
                    _bitmap.Dispose();
                    _bitmap = null;
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
                        _bitmap = Accord.Imaging.Image.Clone((System.Drawing.Bitmap)img, PixelFormat.Format24bppRgb);
                        _bitmap = Grayscale.CommonAlgorithms.RMY.Apply(_bitmap);
                    }
                }
            }
            catch(Exception) {
                Manual = true;
            } finally {
                sw.Stop();
                Console.WriteLine("Took {0} ms to load image bitmap", sw.ElapsedMilliseconds);
            }
        }

        public System.Drawing.Bitmap ShowBitmap {
            get {
                return _bitmap;
            }
        }

        public void ApplyCannyFilter(byte low, byte high, double sigma)
        {

            var f = new SobelEdgeDetector();

            var filter = new CannyEdgeDetector(low, high, sigma);
            _bitmap = filter.Apply(_bitmap);
            OnPropertyChanged("ShowBitmap");
        }

        public long Id { get; set; }

        public BuletinVotVM VotVM {
            get {
                return new BuletinVotVM(ShortFilename, Processed, Nullified, Manual);
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

                Id = (long)Database.ExecuteScalar("SELECT id from Votes order by id desc limit 1");

            } else {
                //update
                var command = String.Format("update Votes set filename='{0}', processed={1}, nullified={2}, manual={3}, result='{4}' where id={5}", FileName, processed, nullified, manual, result.ToString(), Id);
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
                    new Sharpen().ApplyInPlace(_bitmap);
                    //_bitmap = Accord.Imaging.Image.Clone(_wBitmap, PixelFormat.Format24bppRgb);
                    return true;
                case StepType.CannyFilter:
                    new CannyEdgeDetector(0, 30, 0.2).ApplyInPlace(_bitmap);
                    //_bitmap = Accord.Imaging.Image.Clone(_wBitmap, PixelFormat.Format24bppRgb);
                    return true;
                case StepType.SobelEdgeDetection:
                    new SobelEdgeDetector().ApplyInPlace(_bitmap);
                    //_bitmap = Accord.Imaging.Image.Clone(_wBitmap, PixelFormat.Format24bppRgb);
                    return true;
                case StepType.DifferenceEdgeDetection:
                    new DifferenceEdgeDetector().ApplyInPlace(_bitmap);
                    //_bitmap = Accord.Imaging.Image.Clone(_wBitmap, PixelFormat.Format24bppRgb);
                    return true;
                case StepType.Median:
                    new Median().ApplyInPlace(_bitmap);
                    //_bitmap = Accord.Imaging.Image.Clone(_wBitmap, PixelFormat.Format24bppRgb);
                    return true;
                case StepType.BlobCounter:
                    _bitmap = Accord.Imaging.Image.Clone(_bitmap, PixelFormat.Format24bppRgb);
                    return BlobCounter();
                case StepType.HoughLines:
                    HoughLines();
                    break;
                case StepType.VoteCounter:
                    var result = new bool[App.OptiuniVot.Count];
                    var countok = VoteCounter(out result);

                    _processed = countok;
                    _manual = !countok;
                    _result = result;

                    return countok;
            }
            return true;
        }

        private bool VoteCounter(out bool[] result)
        {
            var rowsCount = App.OptiuniVot.Count / 2 + App.OptiuniVot.Count % 2;
            LeftBoxes.Clear();
            RightBoxes.Clear();

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

            Dictionary<int, bool> votes = new Dictionary<int, bool>();


            using (var g = Graphics.FromImage(_bitmap))
            using (Pen pen = new Pen(Color.Yellow, 2)) {

                int index = 0;

                Stopwatch sw = new Stopwatch();
                sw.Start();

                for (var i = 0; i < LeftBoxes.Count; i++) {
                    var vote = PaintBox(g, pen, LeftBoxes[i]);
                    votes[index++] = vote;
                }
                for (var i = 0; i < RightBoxes.Count; i++) {
                    var vote = PaintBox(g, pen, RightBoxes[i]);
                    votes[index++] = vote;
                }

                sw.Stop();
                Console.WriteLine(String.Format("Took {0} ms to compute votes.", sw.ElapsedMilliseconds));
            }

            SetVotes(votes);
            result = Votes.OrderBy(v => v.NrCrt).Select(p => p.Optiune).ToArray();

            return true;
        }

        private bool PaintBox(Graphics g, Pen pen, Rectangle r)
        {
            bool vote = false;

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
            //System.Diagnostics.Debug.WriteLine("{0}  {1}  {2}  {3}", alpha, red, green, blue);

            if ((red+green+blue) / 3 > 50) {
                vote = true;
                color = Color.White;
            }

            g.DrawRectangle(pen, r);
            System.Drawing.Brush b = new System.Drawing.SolidBrush(color);
            g.FillRectangle(b, Rectangle.FromLTRB(r.Left+50, r.Top, r.Right+50, r.Bottom));
            b.Dispose();

            return vote;
        }

        private bool BlobCounter()
        {

            // lock image
            BitmapData bitmapData = _bitmap.LockBits(ImageLockMode.ReadWrite);

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
            _bitmap.UnlockBits(bitmapData);

            // step 3 - check objects' type and highlight
            SimpleShapeChecker shapeChecker = new SimpleShapeChecker();

            using (var g = Graphics.FromImage(_bitmap))
            using (Pen pen = new Pen(Color.Red, 2)) {

                for (int i = 0; i < blobs.Length; i++) {

                    //Debug.WriteLine(String.Format("Blob {0}: W: {1}   H:{2}   ", i, blobs[i].Rectangle.Width, blobs[i].Rectangle.Height));

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

                RectLeft = blobs.OrderBy(b => b.Rectangle.Left).First().Rectangle;
                RectRight = blobs.OrderBy(b => b.Rectangle.Left).Last().Rectangle;
                return true;
            }
        }

        private void HoughLines()
        {
            var image = Accord.Imaging.Image.Clone(_bitmap, PixelFormat.Format24bppRgb);
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

            
            if (_bitmap == null) {
                LoadImageBitmap();
            }

            List<Step> steps = new List<Step>();
            steps.Add(new Step() { Type = StepType.Median });
            steps.Add(new Step() { Type = StepType.Sharpen });
            steps.Add(new Step() { Type = StepType.DifferenceEdgeDetection });
            steps.Add(new Step() { Type = StepType.BlobCounter });
            steps.Add(new Step() { Type = StepType.VoteCounter });
            bool ok = true;

            Stopwatch sw = new Stopwatch();
            

            foreach(var s in steps) {

                sw.Restart();

                ok = DetectionStep(s);

                sw.Stop();
                Console.WriteLine("Took {0} ms to do detect step {1}", sw.ElapsedMilliseconds, s.Type);

                if (!ok) {
                    break;
                }
            }


            OnPropertyChanged("Processed");
            OnPropertyChanged("Manual");
            OnPropertyChanged("Nullified");
            OnPropertyChanged("VotVM");

            sw.Restart();
            Save();

            sw.Stop();
            Console.WriteLine("Took {0} ms to save.", sw.ElapsedMilliseconds);

            _bitmap.Save(Guid.NewGuid().ToString() + ".bmp");
        }
    }
}
