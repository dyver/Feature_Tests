#include <iostream>

class Hello {
    public:
        int helloWorld() {
            return 0;
        }
};

struct Generic {
};

// SFINAE test
template <typename TestedClass> class hasFunctionHelloWorld {
    private:
        using yes = char[1];
        using no = char[2];
        template <typename Option> static yes& test(decltype(&Option::helloWorld));
        template <typename Option> static no& test(...);
    public:
        enum { value = sizeof(test<TestedClass>(0)) == sizeof(yes) };
};

int main() {
    std::cout << "Does the class Hello has function helloWord? ";
    std::cout << (hasFunctionHelloWorld<Hello>::value ? "Yes" : "No") << std::endl;
    std::cout << "Does the class Generic has function helloWord? ";
    std::cout << (hasFunctionHelloWorld<Generic>::value ? "Yes" : "No") << std::endl;
    return 0;
}
