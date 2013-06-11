#include <iostream>
#include <string>
#include <chrono> // for time utilities

#include <pqxx/pqxx>

using namespace pqxx;
using namespace std;

#define REPORT_ERROR \
    cout << "In function '" << __func__ << "' we have a problem: " << e.what() << endl;


class BaseTest
{
    public :
        BaseTest()
        {
            c.reset(new connection("dbname = sql_test user = postgres password = 123"));
            cout << "Connected to " << c->dbname() << endl;
        }

        ~BaseTest() {}

        void doInfoWork()
        {
            try {
                work w(*c);
                result r = w.exec("select * from messages");
                report(r);
            } catch (const exception& e) {
                REPORT_ERROR
            }
        }

        void doInsertWork()
        {
            work w(*c);
            for (auto i = 0; i < 100; ++i) {
                stringstream query;
                query << "insert into messages values (";
                query << i << ", 'Test" << i << "')";
                w.exec(query.str());
            }
            w.commit();
        }

        void doCreateWork()
        {
            work w(*c);
            w.exec(
                    "create table messages ("
                        "id integer,"
                        "text varchar(128)"
                    ");"
            );
            w.commit();
        }

        void doDropWork()
        {
            try {
                work w(*c);
                w.exec("drop table messages");
                w.commit();
            } catch (const exception& e) {
                REPORT_ERROR
            }
        }
    private :
        void report(const result& r)
        {
            cout << "Found " << r.size() << " rows." << endl;
            cout << "Number of columns: " << r[0].size() << endl;
            //for (result::const_iterator i = r.begin(); i != r.end(); ++i) {
            if (r.size() > ReportedRawsLimit) {
                cout << "Too many rows to report" << endl;
                return;
            }
            for (result::size_type i = 0; i < r.size(); ++i) {
                cout << " | ";
                for (unsigned int j = 0; j < r[i].size(); ++j) {
                    cout << r[i][j].c_str() << " | ";
                }
                cout << endl;
            }
        }
        unique_ptr<connection> c;
        static const unsigned int ReportedRawsLimit = 20;
};

#define BEFORE_METHOD \
    { \
        auto before = system_clock::now();
#define AFTER_METHOD \
        microseconds elapsed = \
                duration_cast<microseconds>(system_clock::now() - before); \
        cout << "Elapsed " << elapsed.count() << " microseconds." << endl; \
    }



int main(void)
{
    using namespace std::chrono;
    BEFORE_METHOD
    try {
        BaseTest bt;
        cout << "Current table state:" << endl;
        BEFORE_METHOD
        bt.doInfoWork();
        AFTER_METHOD
        cout << "Dropping table." << endl;
        BEFORE_METHOD
        bt.doDropWork();
        AFTER_METHOD
        cout << "Creating new table." << endl;
        BEFORE_METHOD
        bt.doCreateWork();
        AFTER_METHOD
        cout << "Inserting some values." << endl;
        BEFORE_METHOD
        bt.doInsertWork();
        AFTER_METHOD
        cout << "New table state:" << endl;
        BEFORE_METHOD
        bt.doInfoWork();
        AFTER_METHOD
    } catch (const exception& e) {
        REPORT_ERROR
    }
    AFTER_METHOD
    return 0;
}
