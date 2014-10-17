#include <++c.h>

// override controls: override & final

class OverrideBase {
    public:
        virtual int functionToBeOverrided();
        virtual int functionToBeFinalized();
};

class OverrideDerivation : public OverrideBase {
    public:
        int functionToBeOverrided() override;
        int functionToBeFinalized() final;
};

void OverrideControl() {
}
