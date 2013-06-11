#include <iostream>
#include <unistd.h>

#include "parallel.hpp"

using namespace std;
using namespace parallel;

extern Mutex coutMutex;

void msleep(int msec) { usleep(msec * 1000); }

struct Waiter
{
    Waiter() { msleep(1000); }
};

class ListenerThread : public Waiter
{
    public:
        ListenerThread() : Waiter() { pth = new Thread<ListenerThread>("Listener"); pth->start(); }
        void start() { pth->start(); }
        void stop() { pth->stop(); }
        ~ListenerThread() { cout << "~ListenerThread" << endl; }
    protected:
    private:
        Thread<ListenerThread>* pth;
        void run() {
            { MutexLocker ml(coutMutex);
                cout << "Within ListenerThread" << endl;
                msleep(1000);
            }
        }
};

int main(void)
{
    ListenerThread lt; // forbidden
    delete &lt;
    ListenerThread *plt = new ListenerThread();
    cout << "^^^^^^^^^" << endl;
    plt->start();
    msleep(2150);
    cout << "^^^^^^^^^" << endl;
    plt->start();
    plt->stop();
    Thread<ListenerThread>::destroy(plt);
    plt = new ListenerThread();
    plt->start();
    Thread<ListenerThread>::destroy(plt);
    /////delete plt; // forbidden
    //msleep(5);

    for (int i = 0; i < 10; ++i) {
        new ListenerThread();
    }
    int j = 10;
    while (j --> 0) cout << "*";
    cout << endl;
    return 0;
}
