#include <++cpp11.h>

// template alias
// !!! PARTIALLY DONT WORK !!!

template <typename T> using VectorAlias = std::vector<std::vector<int>>;
using PointerFunctionAlias = void (*)(double);
using PointerFunctionWithSuffixAlias = auto (*)(int) -> int;
//using LambdaFunctionAlias = [](double) -> void;

void TemplateAlias() {
    VectorAlias<int> v;
}
