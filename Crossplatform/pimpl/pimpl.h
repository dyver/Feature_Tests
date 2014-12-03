#include <memory>

class Pimpl {
    public:
        Pimpl();
        ~Pimpl();
    private:
        class Imp;
        std::auto_ptr<Imp> imp;
};
