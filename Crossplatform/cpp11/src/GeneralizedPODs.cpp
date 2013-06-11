#include <string.h> // for memcpy

#include <++cpp11.h>

// PODs (generalized)

struct GeneralizedPODstruct {
    int a;
    GeneralizedPODstruct(int aa) : a(aa) {} // ctor doesn't affect layout
};

void GeneralizedPODs() {
    GeneralizedPODstruct pod1(100);
    GeneralizedPODstruct pod2(200);
    memcpy(&pod2, &pod1, sizeof(GeneralizedPODstruct));
}
