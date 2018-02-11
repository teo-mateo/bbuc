using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BaroulBucuresti.Vot.models
{
    public class Vot
    {
        public Vot() { }

        public Vot(string filename)
        {
            _filename = filename;
            _result = new bool[App.OptiuniVot.Count];
        }

        public long Id { get; set; }

        private string _filename;
        public string FileName {
            get { return _filename; }
            set {
                _filename = value;
                Save();
            }
        }

        private bool _processed;
        public bool Processed {
            get { return _processed; }
            set {
                _processed = value;
                Save();
            }
        }

        private bool _nullified;
        public bool Nullified {
            get { return _nullified; }
            set {
                _nullified = value;
                Save();
            }
        }

        private bool _manual;
        public bool Manual {
            get { return _manual; }
            set {
                _manual = value;
                Save();
            }
        }

        private bool[] _result;
        public bool[] Result {
            get { return _result; }
            set {
                _result = value;
                Save();
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
    }
}
