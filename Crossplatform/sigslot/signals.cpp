//#define SIGSLOT_PURE_ISO
//#define NULL nullptr
#define SIGSLOT_DEFAULT_MT_POLICY multi_threaded_global
#include "sigslot.h"

namespace Signals
{
    class SignalSender
    {
        public :
            sigslot::signal0<> action;
            ~SignalSender() {}
    };

    class SignalReceiver : public sigslot::has_slots<>
    {
        private :
            class locker : public sigslot::lock_block<sigslot::multi_threaded_global>
            {
                public :
                locker(SignalReceiver *p) : sigslot::lock_block<sigslot::multi_threaded_global>(p) {}
            };
        public :
            void OnAction();
            ~SignalReceiver() {}
    };
}

#define ScopeLocker locker(this);

void Signals::SignalReceiver::OnAction()
{
   // sigslot::lock_block</*sigslot::multi_threaded_global*/> lock(this);
    ScopeLocker;
}

#include <iostream> // for console output

#include <exception>

using namespace Signals;

int main()
{
    // signals
    SignalSender ss;
    SignalReceiver sr;
    ss.action.connect(&sr, &SignalReceiver::OnAction);

    return 0;
}
