#include <++c.h>

// decltype - the type of an expression

inline int decltypeFunction() {
    return 42;
}

void DeclType() {
    std::vector<int> objType1(1);
    decltype(objType1) objType2(objType1);
    objType2[0]++;
    decltype((objType1)) objType1RefTo(objType1);
    objType1RefTo[0]++;
    decltype(decltypeFunction()) i = 10;
    i++;
}
