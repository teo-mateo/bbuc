using Ghostscript.NET.Rasterizer;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace BaroulBucuresti.Vot
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {

        public MainWindow()
        {
            InitializeComponent();

            _votes = new List<models.Vot>();
            DataContext = this;
            LoadVotes();
        }

        private models.Vot _selectedVot;
        public models.Vot SelectedVot {
            get {
                return _selectedVot;
            }
            set {
                _selectedVot = value;
                OnPropertyChanged("SelectedVot");

                if(_selectedVot != null) {

                    if (_selectedVot.ShowBitmap == null) {
                        _selectedVot.LoadImageBitmap();
                    }

                    Preview(_selectedVot.ShowBitmap);
                }
            }
        }

        private void OnPropertyChanged(string name)
        {
            if (PropertyChanged != null) {
                PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
        }
        public event PropertyChangedEventHandler PropertyChanged;

        private void RibbonApplicationMenuItem_Click(object sender, RoutedEventArgs e)
        {

        }

        public string VoteSource { get; set; }

        private List<models.Vot> _votes;
        public List<models.Vot> Votes {
            get { return _votes; }
        }

        private void mnuExit_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void mnuOptiuniVot_Click(object sender, RoutedEventArgs e)
        {
            var ov = new OptiuniVot();
            ov.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            ov.ShowDialog();

            if (ov.ChangesWereMade) {
                LoadVotes();
            }
        }

        private void mnuSetariAplicatie_Click(object sender, RoutedEventArgs e)
        {

        }

        private void btnRibbon1_Click(object sender, RoutedEventArgs e)
        {

        }

        private void btnSursaVoturi_Click(object sender, RoutedEventArgs e)
        {
            var source = Database.GetSetting(Constants.KEY_VOTE_SOURCE);

            var directory = "";
            if (!String.IsNullOrEmpty(source)) {
                directory = source;
            }

            using (var fbd = new System.Windows.Forms.FolderBrowserDialog()) {
                if (Directory.Exists(directory)) {
                    fbd.SelectedPath = directory;
                }

                if (fbd.ShowDialog() == System.Windows.Forms.DialogResult.OK) {
                    if (MessageBox.Show(
                        "Există voturi inregistrate pentru această sesiune de lucru.\nModificarea sursei fisierelor va duce la ștergerea voturilor.",
                        "Confirmare",
                        MessageBoxButton.OKCancel,
                        MessageBoxImage.Exclamation) == MessageBoxResult.Cancel) {
                        return;
                    }


                    Database.SetSetting(Constants.KEY_VOTE_SOURCE, fbd.SelectedPath);


                    //var workspace = System.IO.Path.Combine(fbd.SelectedPath, "Workspace");
                    //if (!Directory.Exists(workspace)) {
                    //    Directory.CreateDirectory(workspace);
                    //}

                    //convert
                    //var files = Directory.EnumerateFiles(fbd.SelectedPath);
                    //foreach(var f in files) {
                    //    if (f.EndsWith("pdf", StringComparison.InvariantCultureIgnoreCase)) {

                    //        var fn = new FileInfo(f).Name.ToLower().Replace(".pdf", ".png");

                    //        int desired_x_dpi = 200;
                    //        int desired_y_dpi = 200;

                    //        using (var rasterizer = new GhostscriptRasterizer()) {
                    //            rasterizer.Open(f);

                    //            if (rasterizer.PageCount > 1) {
                    //                continue;
                    //            }

                    //            for (var pageNumber = 1; pageNumber <= rasterizer.PageCount; pageNumber++) {
                    //                var pageFilePath = System.IO.Path.Combine(workspace, fn);

                    //                if (File.Exists(pageFilePath)) {
                    //                    File.Delete(pageFilePath);
                    //                }


                    //                var img = rasterizer.GetPage(desired_x_dpi, desired_y_dpi, pageNumber);
                    //                img.Save(pageFilePath, System.Drawing.Imaging.ImageFormat.Png);
                    //                img.Dispose();

                    //                Console.WriteLine(pageFilePath);
                    //            }
                    //        }
                    //    }
                    //}

                    //Database.SetSetting(Constants.KEY_VOTE_SOURCE, workspace);

                    LoadVotes();
                }
            }
        }

        private void LoadVotes()
        {
            string sourcePath = Database.GetSetting(Constants.KEY_VOTE_SOURCE); 
            if(string.IsNullOrEmpty(sourcePath) || !Directory.Exists(sourcePath)) {
                return;
            }

            _votes = new List<models.Vot>();

            var files = Directory.EnumerateFiles(sourcePath);
            foreach (var f in files) {
                var v = new models.Vot(f);
                v.Save();
                _votes.Add(v);
            }
            OnPropertyChanged("Votes");
        }

        private void btnDetect_Click(object sender, RoutedEventArgs e)
        {
            if (SelectedVot == null) {
                return;
            }

            SelectedVot.Detect();
            Preview(SelectedVot.ShowBitmap);
        }

        private void Preview(System.Drawing.Bitmap bmp)
        {

            if (SelectedVot == null) {
                return;
            }

            if (SelectedVot.ShowBitmap == null) {
                SelectedVot.LoadImageBitmap();
            }

            var ms = new MemoryStream();
            ((System.Drawing.Bitmap)SelectedVot.ShowBitmap).Save(ms, System.Drawing.Imaging.ImageFormat.Bmp);
            BitmapImage image = new BitmapImage();
            image.BeginInit();
            ms.Seek(0, SeekOrigin.Begin);
            image.StreamSource = ms;
            image.EndInit();
            imgPreview.Source = image;
        }

        private void btnSharpen_Click(object sender, RoutedEventArgs e)
        {
            if (SelectedVot == null) {
                return;
            }

            SelectedVot.DetectionStep(new Detection.Step() { Type = Detection.StepType.Sharpen });
            Preview(SelectedVot.ShowBitmap);
        }

        private void btnMedian_Click(object sender, RoutedEventArgs e)
        {
            if (SelectedVot == null) {
                return;
            }

            SelectedVot.DetectionStep(new Detection.Step() { Type = Detection.StepType.Median });
            Preview(SelectedVot.ShowBitmap);
        }

        private void btnBlobCounter_Click(object sender, RoutedEventArgs e)
        {
            if (SelectedVot == null) {
                return;
            }

            SelectedVot.DetectionStep(new Detection.Step() { Type = Detection.StepType.BlobCounter });
            Preview(SelectedVot.ShowBitmap);
        }

        private void btnSobel_Click(object sender, RoutedEventArgs e)
        {
            if (SelectedVot == null) {
                return;
            }

            SelectedVot.DetectionStep(new Detection.Step() { Type = Detection.StepType.SobelEdgeDetection });
            Preview(SelectedVot.ShowBitmap);
        }

        private void btnCanny_Click(object sender, RoutedEventArgs e)
        {
            if (SelectedVot == null) {
                return;
            }

            SelectedVot.DetectionStep(new Detection.Step() { Type = Detection.StepType.CannyFilter });
            Preview(SelectedVot.ShowBitmap);
        }

        private void btnDifference_Click(object sender, RoutedEventArgs e)
        {
            if (SelectedVot == null) {
                return;
            }

            SelectedVot.DetectionStep(new Detection.Step() { Type = Detection.StepType.DifferenceEdgeDetection });
            Preview(SelectedVot.ShowBitmap);
        }

        private void btnHoughLines_Click(object sender, RoutedEventArgs e)
        {
            if (SelectedVot == null) {
                return;
            }

            SelectedVot.DetectionStep(new Detection.Step() { Type = Detection.StepType.HoughLines });
            Preview(SelectedVot.ShowBitmap);
        }

        private void btnSave_Click(object sender, RoutedEventArgs e)
        {
            var fn = DateTime.Now.Ticks + ".bmp";
            SelectedVot.ShowBitmap.Save(fn);
        }

        private void btnManual_Click(object sender, RoutedEventArgs e)
        {
            if (SelectedVot == null) {
                return;
            }

            SelectedVot.Manual = !SelectedVot.Manual;
            SelectedVot.LoadImageBitmap();

            Preview(SelectedVot.ShowBitmap);
        }

        bool _cancel;

        private void btnAutomat_Click(object sender, RoutedEventArgs e)
        {
            if (btnAutomat.Label == "Automat") {
                btnAutomat.Label = "Opreste";

                _cancel = false;

                Task.Run(() => {
                    foreach (var v in Votes) {
                        System.Diagnostics.Debug.WriteLine(v.FileName);
                        if (!v.Manual && !v.Nullified && !v.Processed) {

                            //Thread.Sleep(300);
                            if (_cancel) {
                                break;
                            }

                            v.LoadImageBitmap();
                            v.Detect();

                            Dispatcher.Invoke(() => {
                                try {
                                    SelectedVot = v;
                                }
                                catch(Exception ex) {

                                }
                            });
                        }
                    }

                    Dispatcher.Invoke(() => {
                        btnAutomat.Label = "Automat";
                    });
                });

            } else {
                _cancel = true;
                btnAutomat.Label = "Automat";
            }
        }
    }
}
