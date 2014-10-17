#include <++c.h>

// rvalue references

class RValueReferenceClass {
    public:
        RValueReferenceClass(int i) {
            data = new int(i);
        }
        // move constructor
        RValueReferenceClass(RValueReferenceClass&& sample) {
            data = sample.data;
            sample.data = 0;
        }
        // move assignment
        RValueReferenceClass &operator=(RValueReferenceClass&& sample) {
            delete data;
            data = sample.data;
            sample.data = 0;
            return *this;
        }
        ~RValueReferenceClass() {
            delete data;
        }
    private:
        int* data;
};

void RValueReferences() {
    RValueReferenceClass rvr(10);
    RValueReferenceClass rvr2(std::move(rvr));
    RValueReferenceClass rvr3(20);
    rvr2 = std::move(rvr3);
}
