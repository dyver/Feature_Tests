#include <iostream>
#include <memory>
#include <map>
#include <algorithm>

using namespace std;

// class Interface {
//     public:
//         virtual ~Interface() {}
//         virtual void hello() = 0;
// };

template <class T> class Parameter {
    public:
        Parameter() {
            value = T();
        }
        void setValue(const T& value) {
            this->value = value;
        }
        T getValue() {
            return value;
        }
    private:
        T value;
};

//using IntParameter = Parameter<int>;
//using DoubleParameter = Parameter<double>;

class Container {
    public:
        Parameter<int>& getInt(const string& name) {
            static Parameter<int> def;
            auto it = intParameters.find(name);
            return it != intParameters.end() ? it->second : def;
        }
        Parameter<double>& getDouble(const string& name) {
            static Parameter<double> def;
            auto it = doubleParameters.find(name);
            return it != doubleParameters.end() ? it->second : def;
        }
    private:
        map<string, Parameter<int>> intParameters;
        map<string, Parameter<double>> doubleParameters;
};

int main() {
    Parameter<int> p;
    p.setValue(10);
    cout << p.getValue() << endl;
    return 0;
}
