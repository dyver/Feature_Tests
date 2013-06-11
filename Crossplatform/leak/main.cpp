#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class Test
{
    public :
        Test() : i(0) { construct(); }
        Test(const Test& sample) { i = sample.i; construct(); }
        ~Test() { destruct(); }
        int state() { return i; }
        static int get_balance() { return balance_counter; }
        static void reset_balance() { balance_counter = 0; }
    private :
        void construct() {
            static int call_counter = 0;
            ++call_counter;
            i = call_counter;
            ++balance_counter;
            cout << "ctor: balance=" << balance_counter << " call=" << call_counter << endl;
        }
        void destruct() {
            static int call_counter = 0;
            ++call_counter;
            --balance_counter;
            cout << "dtor: balance=" << balance_counter << " call=" << call_counter << endl;
        }
        static int balance_counter;
        int i;
};

int Test::balance_counter = 0;

class Base
{
public :
    Base() {}
    virtual ~Base() {
        cout << "~Base" << endl;
    }
};

class Derived : public Base
{
public :
    Derived() {}
    ~Derived() {
        cout << "~Derived" << endl;
    }
};

void report()
{
    if (Test::get_balance() == 0)
        cout << "SUCCESS: all objects destructed successfully!" << endl;
    else
        cout << "FAIL: remain some objects!" << endl;
}



int main(void)
{
class Deleter
{
    public:
        void operator()(int* pi) { delete pi; }
};
    std::vector<int *> vi;
    vi.push_back(new int(1));
    for_each(vi.begin(), vi.end(), Deleter());

    typedef vector<Test> VT;
    typedef vector<Test*> VPT;
    typedef auto_ptr<Test> APT;
    typedef vector<APT> VAPT;
    typedef unique_ptr<Test> UPT;
    typedef vector<UPT> VUPT;

    {
        Test::reset_balance();
        VT vt;
        //vt.reserve(100);
        // если не резервировать, то объекты перемещаются при добавлении нового объекта
        cout << "Filling vector of Test" << endl;
        for (int i = 0; i < 5; ++i) vt.emplace_back(Test());
        cout << "Destructing vector of Test" << endl;
    }
    report();
    {
        Test::reset_balance();
        VPT vt;
        cout << "Filling vector of Test*" << endl;
        for (int i = 0; i < 10; ++i) vt.push_back(new Test());
        cout << "Destructing vector of Test*" << endl;
    }
    report();
    {
        Test::reset_balance();
        VAPT vt;
        cout << "Filling vector of auto_ptr<Test>" << endl;
        for (int i = 0; i < 10; ++i) vt.push_back(APT(new Test()));
        auto comparator = [](const APT &a, const APT &b) -> bool {
                return a->state() > b->state();
        };
        cout << "Before sort" << endl;
        for (const auto &it : vt) cout << " " << it->state();
        cout << endl;
        sort(vt.begin(), vt.end(), comparator);
        cout << "After sort" << endl;
        for (const auto &it : vt) cout << " " << it->state();
        cout << endl;
        cout << "Destructing vector of auto_ptr<Test>" << endl;
    }
    report();
    {
        Test::reset_balance();
        VUPT vt;
        cout << "Filling vector of unique_ptr<Test>" << endl;
        for (int i = 0; i < 10; ++i) vt.push_back(UPT(new Test()));
        cout << "Destructing vector of unique_ptr<Test>" << endl;
    }
    report();

    Base* b = new Derived();
    delete b;

    return 0;
}