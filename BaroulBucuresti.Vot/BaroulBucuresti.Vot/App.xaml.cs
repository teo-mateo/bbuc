using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SQLite;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace BaroulBucuresti.Vot
{
    public static class Constants
    {
        public static readonly string SQLITE_FILE = "db.sqlite";
        public static string SQLITE_FILE_NAME_FULL {
            get {
                return Path.Combine(AppDomain.CurrentDomain.BaseDirectory + SQLITE_FILE);
            }
        }
        public static string SQLITE_CN {
            get {
                return String.Format("Data source={0};Version=3", SQLITE_FILE);
            }
        }
    }

    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private static List<OptiuneVot> _optiuniVot;
        public static List<OptiuneVot> OptiuniVot {
            get {
                if (_optiuniVot == null) {
                    _optiuniVot = new List<OptiuneVot>();
                    var optiuni = Database.ExecuteQuery("select * from VoteOptions order by nrcrt asc").ToArray();
                    for (int i = 0; i < optiuni.Count(); i++) {
                        _optiuniVot.Add(new OptiuneVot() {
                            NrCrt = (int)optiuni[i].nrcrt,
                            Name = (string)optiuni[i].name
                        });
                    }
                }
                return _optiuniVot;
            }
            set {
                _optiuniVot = value;
            }
        }

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            AppDomain.CurrentDomain.UnhandledException += CurrentDomain_UnhandledException;

            if (!File.Exists(Constants.SQLITE_FILE_NAME_FULL)) {
                SQLiteConnection.CreateFile(Constants.SQLITE_FILE_NAME_FULL);
            }

            if (!Database.TableExists("VoteOptions")) {
                Database.ExecuteNonQuery("create table VoteOptions (id integer primary key autoincrement, nrcrt integer, name text)");
                
            }

            if (!Database.TableExists("Votes")) {
                Database.ExecuteNonQuery("create table Votes (id integer primary key autoincrement, filename varchar(1000), processed integer, nullified integer, manual integer, result text)");
            }

            if (!Database.TableExists("Settings")) {
                Database.ExecuteNonQuery("create table Settings (key text primary key, value text)");
            }

            models.Vot v = new models.Vot("fisier.png");
            v.Update();
        }

        private void CurrentDomain_UnhandledException(object sender, UnhandledExceptionEventArgs e)
        {
            MessageBox.Show(e.ExceptionObject.ToString());
            Application.Current.Shutdown();
        }
    }
}
