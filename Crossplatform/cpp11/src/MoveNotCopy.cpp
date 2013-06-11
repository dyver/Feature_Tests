#include <++cpp11.h>

// control of defaults: move and copy

template<typename T> class MoveNotCopyClass {
    public:
        MoveNotCopyClass(T* pp) : p{pp} {}
        // user-defined destructor: no implicit copy or move
        ~MoveNotCopyClass() { delete p; }
        // transfer ownership
        MoveNotCopyClass(MoveNotCopyClass&& h) : p{h.p} { h.p = nullptr; };
        MoveNotCopyClass& operator=(MoveNotCopyClass&& h) {
                delete p; p = h.p; h.p = nullptr; return *this;
        }
        // no copy
        MoveNotCopyClass(const MoveNotCopyClass&) = delete;
        MoveNotCopyClass& operator=(const MoveNotCopyClass&) = delete;
    private:
        T* p;
};

void MoveNotCopy() {
    auto pi = new int();
    auto pj = new int();
    MoveNotCopyClass<int> h1(pi);
    MoveNotCopyClass<int> h2(pj);
    h2 = std::move(h1); // destructing h1
}
