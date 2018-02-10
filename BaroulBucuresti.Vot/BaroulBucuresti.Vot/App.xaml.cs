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
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            if (!File.Exists(Constants.SQLITE_FILE_NAME_FULL)) {
                SQLiteConnection.CreateFile(Constants.SQLITE_FILE_NAME_FULL);
            }

            if (!Database.TableExists("VoteOptions")) {
                Database.ExecuteNonQuery("create table VoteOptions (id integer primary key autoincrement, nrcrt integer, name text)");
                
            }

            if (!Database.TableExists("Votes")) {
                Database.ExecuteNonQuery("create table Votes (id integer primary key autoincrement, filename varchar(1000), nullified integer, manual integer, result text)");
            }

            if (!Database.TableExists("Settings")) {
                Database.ExecuteNonQuery("create table Settings (key text primary key, value text)");
            }
            
            var optiuni = Database.ExecuteQuery("select * from VoteOptions");
            foreach(var o in optiuni) {
                string name = o.name.ToString();
                Debug.WriteLine(name);
            }
            
        }
    }
}
