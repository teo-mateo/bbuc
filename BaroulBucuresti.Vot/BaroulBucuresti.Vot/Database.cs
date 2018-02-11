using System;
using System.Collections.Generic;
using System.Data.SQLite;
using System.Diagnostics;
using System.Dynamic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BaroulBucuresti.Vot
{
    public class Database
    {
        public static SQLiteConnection Connect()
        {
            var c = new SQLiteConnection(Constants.SQLITE_CN);
            c.Open();
            return c;
        }

        public static void ExecuteNonQuery(string command, SQLiteConnection cn=null)
        {
            Debug.WriteLine("(ExecuteNonQuery) " + command);

            bool dispose = false;

            if (cn == null) {
                cn = Connect();
                dispose = true;
            }

            try {
                SQLiteCommand cmd = new SQLiteCommand(cn);
                cmd.CommandText = command;
                cmd.ExecuteNonQuery();
            } finally {
                if (dispose) {
                    try {
                        cn.Close();
                        cn.Dispose();
                    } catch { }
                }
            }
        }

        public static IEnumerable<dynamic> ExecuteQuery(string command, SQLiteConnection cn = null)
        {
            Debug.WriteLine("(ExecuteQuery) " + command);

            bool dispose = false;
            if (cn == null) {
                cn = Connect();
                dispose = true;
            }

            try {
                SQLiteCommand cmd = new SQLiteCommand(cn);
                cmd.CommandText = command;
                var reader = cmd.ExecuteReader();
                
                if (reader.HasRows) {
                    List<dynamic> result = new List<dynamic>();

                    var names = Enumerable.Range(0, reader.FieldCount).Select(reader.GetName).ToList();
                    while (reader.Read()) {
                        var eo = new ExpandoObject() as IDictionary<string, object>;
                        foreach(var name in names) {
                            eo[name] = reader[name];
                        }
                        result.Add(eo);
                    }

                    reader.Close();
                    return result;
                } else {
                    reader.Close();
                    return Enumerable.Empty<dynamic>();
                }
            } finally {
                if (dispose) {
                    try {
                        cn.Close();
                        cn.Dispose();
                    } catch { }
                }
            }
        }

        public static object ExecuteScalar(string command, SQLiteConnection cn = null)
        {
            Debug.WriteLine("(ExecuteScalar) " + command);

            bool dispose = false;
            if (cn == null) {
                cn = Connect();
                dispose = true;
            }

            object o = null;

            try {
                SQLiteCommand cmd = new SQLiteCommand(cn);
                cmd.CommandText = command;
                o = cmd.ExecuteScalar();
            } finally {
                if (dispose) {
                    try {
                        cn.Clone();
                        cn.Dispose();
                    } catch { }
                }
            }

            return o;
        }


        public static bool TableExists(string table)
        {
            return ExecuteQuery(String.Format("select name from sqlite_master where type='table' and name ='{0}'", table)).Any();
        }
    }
}
