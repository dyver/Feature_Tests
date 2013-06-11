#include <++cpp11.h>

// control of defaults: default and delete

class ForbiddenAction {
    public:
        ForbiddenAction() {}
        ForbiddenAction(const ForbiddenAction&) = delete;
        ForbiddenAction& operator=(const ForbiddenAction&) = delete;
};

class DefaultAction {
    public:
        DefaultAction() = default;
        DefaultAction(const DefaultAction&) = default;
        DefaultAction& operator=(const DefaultAction&) = default;
};

void ControlOfDefaults() {
    ForbiddenAction fa1;
    // ForbiddenAction fa2(fa1); // forbidden
    DefaultAction da1;
    DefaultAction da2(da1);
}
