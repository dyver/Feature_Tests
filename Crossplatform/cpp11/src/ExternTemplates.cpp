#include <++cpp11.h>

// extern templates

template <typename T> class ExternTemplate {
    public:
        T t;
};

extern template class ExternTemplate<int>; // supress instantation here

void someFunction() {}

template class ExternTemplate<int>; // point of instantation

void ExternTemplates() {
    ExternTemplate<int> et;
    outHeader("extern templates");
    outIdent();
    std::cout
        << "result = "
        << et.t;
    outTail();
}
