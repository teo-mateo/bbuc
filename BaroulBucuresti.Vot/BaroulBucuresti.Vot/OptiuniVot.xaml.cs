using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace BaroulBucuresti.Vot
{
    /// <summary>
    /// Interaction logic for OptiuniVot.xaml
    /// </summary>
    public partial class OptiuniVot : Window, INotifyPropertyChanged
    {
        public OptiuniVot()
        {
            InitializeComponent();

            StringBuilder sb = new StringBuilder();
            _optiuniVotList = new List<OptiuneVot>();
            var optiuni = Database.ExecuteQuery("select * from VoteOptions order by nrcrt asc").ToArray();
            for (int i = 0; i < optiuni.Count(); i++) {
                sb.Append(optiuni[i].name.ToString());
                sb.Append(Environment.NewLine);

                _optiuniVotList.Add(new OptiuneVot() {
                    NrCrt = (int)optiuni[i].nrcrt,
                    Name = (string)optiuni[i].name
                });
            }

            _optiuniVotText = sb.ToString();

            this.DataContext = this;
        }

        private string _optiuniVotText;
        public string OptiuniVotText {
            get {
                return _optiuniVotText;
            }
            set {
                _optiuniVotText = value;
                _optiuniVotList = new List<OptiuneVot>();
                var split = _optiuniVotText.Split(new string[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries);
                for (int i = 0; i < split.Length; i++) {
                    _optiuniVotList.Add(new OptiuneVot() { NrCrt = i + 1, Name = split[i] });
                }
                OnPropertyChanged("OptiuniVotList");
                OnPropertyChanged("Group1Count");
                OnPropertyChanged("Group2Count");
            }
        }

        private List<OptiuneVot> _optiuniVotList;
        public List<OptiuneVot> OptiuniVotList {
            get {
                return _optiuniVotList;
            }
        }

        public int Group1Count {
            get {
                return _optiuniVotList.Count / 2 + _optiuniVotList.Count % 2;
            }
        }
        public int Group2Count {
            get {
                return _optiuniVotList.Count / 2;
            }
        }

        private void OnPropertyChanged(string name)
        {
            if (PropertyChanged != null) {
                PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
        }
        public event PropertyChangedEventHandler PropertyChanged;

        private void btnOK_Click(object sender, RoutedEventArgs e)
        {
            var voteCount = (Int64)Database.ExecuteScalar("select count(*) from Votes");
            if (voteCount > 0) {
                if (MessageBox.Show("sigur stergem si voturile?", "intrebare", MessageBoxButton.OKCancel) == MessageBoxResult.Cancel) {
                    return;
                }

                Database.ExecuteNonQuery("delete from Votes");
            }

            Database.ExecuteNonQuery("delete from VoteOptions");
            for (int i = 0; i < OptiuniVotList.Count; i++) {
                Database.ExecuteNonQuery(String.Format("insert into VoteOptions (nrcrt, name) values ({0}, '{1}')", OptiuniVotList[i].NrCrt, OptiuniVotList[i].Name));
            }

            //MUST:
            App.OptiuniVot = OptiuniVotList;

            Close();
        }

        private void btnCancel_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }

    public class OptiuneVot
    {
        public int NrCrt { get; set; }
        public string Name { get; set; }
    }
}
