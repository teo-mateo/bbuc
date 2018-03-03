using BaroulBucuresti.Vot.models;
using Ghostscript.NET.Rasterizer;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
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

            _votes = new List<models.BuletinVot>();
            DataContext = this;
            LoadVotes();
        }

        private int _maxVotes = -1;
        public int MaxVotes {
            get {
                if (_maxVotes == -1) {
                    _maxVotes = int.Parse(Database.GetSetting(Constants.KEY_MAXVOTES));
                }

                return _maxVotes;
            }
        }

        private models.BuletinVot _selectedVot;
        public models.BuletinVot SelectedVot {
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

        private List<models.BuletinVot> _votes;
        public List<models.BuletinVot> Votes {
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

                var voteCount = (Int64)Database.ExecuteScalar("select count(*) from Votes");
                if (voteCount > 0) {
                    if (MessageBox.Show(
                        "Există voturi inregistrate pentru această sesiune de lucru.\nModificarea opțiunilor de vot va duce la ștergerea voturilor.",
                        "Confirmare",
                        MessageBoxButton.OKCancel,
                        MessageBoxImage.Exclamation) == MessageBoxResult.Cancel) {
                        return;
                    }

                }

                if (fbd.ShowDialog() == System.Windows.Forms.DialogResult.OK) {

                    Database.ExecuteNonQuery("delete from Votes");
                    Votes.Clear();
                    OnPropertyChanged("Votes");
                    SelectedVot = null;
                    OnPropertyChanged("SelectedVot");
                    if (Clasament != null) {
                        Clasament.Clear();
                        OnPropertyChanged("Clasament");
                    }
                    Database.SetSetting(Constants.KEY_VOTE_SOURCE, fbd.SelectedPath);


                    LoadVotes(fbd.SelectedPath);

                    dgVotes.Items.Refresh();
                    imgPreview.Source = null;
                }
            }
        }

        private void LoadVotes(string source="")
        {
            if (string.IsNullOrEmpty(source)) {

                _votes = new List<models.BuletinVot>();

                var result = Database.ExecuteQuery("select * from Votes");
                foreach(var record in result) {
                    var v = new BuletinVot(record);
                    _votes.Add(v);
                }
            } else {
                string sourcePath = Database.GetSetting(Constants.KEY_VOTE_SOURCE);
                if (string.IsNullOrEmpty(sourcePath) || !Directory.Exists(sourcePath)) {
                    return;
                }



                var files = Directory.EnumerateFiles(sourcePath);
                foreach (var f in files) {
                    var v = new models.BuletinVot(f);
                    v.Save();
                    _votes.Add(v);
                }
            }


            OnPropertyChanged("Votes");
        }

        private void btnDetect_Click(object sender, RoutedEventArgs e)
        {
            if (SelectedVot == null) {
                return;
            }

            Stopwatch sw = new Stopwatch();

            sw.Restart();
            SelectedVot.Detect();
            sw.Stop();
            Console.WriteLine("Took {0} ms to detect.", sw.ElapsedMilliseconds);

            sw.Restart();
            Preview(SelectedVot.ShowBitmap);
            sw.Stop();
            Console.WriteLine("Took {0} ms to preview.", sw.ElapsedMilliseconds);

            sw.Restart();
            NumaraVoturi();
            sw.Stop();
            Console.WriteLine("Took {0} ms to count all votes", sw.ElapsedMilliseconds);
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
                                    NumaraVoturi();
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

        public List<ClasamentVM> Clasament { get; set; }

        private void btnNumara_Click(object sender, RoutedEventArgs e)
        {

            NumaraVoturi();
        }

        private void NumaraVoturi()
        {
            Clasament = App.OptiuniVot.Select(o => new ClasamentVM {
                NrCrt = o.NrCrt,
                Candidat = o.Name,
                Voturi = Votes
                .Where(v => !v.Nullified)
                .Select(v => {
                    if (v.Result[o.NrCrt - 1]) {
                        return 1;
                    } else {
                        return 0;
                    }
                }).Sum()
            })
            .OrderByDescending(o => o.Voturi)
            .ThenBy(o => o.NrCrt)
            .ToList();

            OnPropertyChanged("Clasament");
        }

        private void mnuAnulat_Click(object sender, RoutedEventArgs e)
        {
            if (SelectedVot != null) {
                SelectedVot.Nullified = !SelectedVot.Nullified;
            }
        }

        private void mnuProcesat_Click(object sender, RoutedEventArgs e)
        {
            if (SelectedVot != null) {
                SelectedVot.Processed = !SelectedVot.Processed;
            }
        }

        private void mnuManual_Click(object sender, RoutedEventArgs e)
        {
            if (SelectedVot != null) {
                SelectedVot.Manual = !SelectedVot.Manual;
            }
        }

        private void btnClear_Click(object sender, RoutedEventArgs e)
        {
            Votes.Clear();
            SelectedVot = null;
            OnPropertyChanged("Votes");
            dgVotes.Items.Refresh();
        }
    }

    public class ClasamentVM
    {
        public int NrCrt { get; set; }
        public string Candidat { get; set; }
        public int Voturi { get; set; }
    }
}
