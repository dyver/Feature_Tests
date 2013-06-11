#include <iostream>
#include <unistd.h>

#include "callback.hpp"
#include "parallel.hpp"

#include "arc_event.h"
#include "data_msg_type.h"
#include "data_text_message.h"
#include "data_arc.h"

using namespace std;
using namespace callback;
using namespace parallel;
using namespace tmsg;

void msleep(int msec) { usleep(msec * 1000); }

typedef OnEventBase<0, int> ChangedMapValue;

class OnChangedMapValue : public ChangedMapValue
{
    public:
        void invoke(const int& d) {
            { MutexLocker ml(coutMutex);
                cout << "Event 'OnChangedMapValue' with parameter " << d << endl;
            }
        }
};

class OnChanged2MapValue : public ChangedMapValue
{
    public:
        void invoke(const int& d) {
            { MutexLocker ml(coutMutex);
                cout << "Event 'OnChanged2MapValue' with parameter " << d << endl;
            }
        }
};

typedef OnEventBase<1, int> AnotherChangedMapValue;

class OnAnotherChangedMapValue : public AnotherChangedMapValue
{
    public:
        void invoke(const int& d) {
            { MutexLocker ml(coutMutex);
                cout << "Event 'AnotherChangedMapValue' with parameter " << d << endl;
            }
        }
};

struct Waiter
{
    Waiter() { msleep(0); }
};

class ListenerThread : public Thread, public Waiter
{
    public:
        ListenerThread() : Thread("Listener", true), Waiter() { constructed = true; }
        ~ListenerThread() { cout << "~ListenerThread" << endl; constructed = false; }
    private:
        void run() {
            { MutexLocker ml(coutMutex);
                cout << "Within ListenerThread" << endl;
            }
        }
};

void arc_eventMapFunc(msg_event_t eventType, void* listener, uint dataId, const char* mapName, int mapKey )
{
    cout << "arc_eventMapFunc: " << "eventType=" << eventType << " dataId=" << dataId << endl;
}

const char* MapName = "Отправленные текстовые собщения";
int key = 666;
arc::Map postedDataMap(MapName);

void storeMessage()
{
    Message m;
    m.setText("ПРИВЕТ МЕДВЕД!!!");
    m.setTextId(24);
    time_t tt;
    m.setTime(time(&tt));
    postedDataMap.save(key, &m);
    //m.msg()->set_stateAndSave(sSending);
}

void subscribe()
{
    msg_event_t eventType = msg_event_t(/*eCreate|*/eChange/*|eChangeStatus|eDelete*/);
    void* listener = 0;
    arc_subscribeOnMapEventByMapKey(arc_eventMapFunc, eventType, MapName, key, listener);
}

void unsubscribe()
{
    void* listener = 0;
    arc_unsubscribeEvent(listener);
}

int main(void)
{
    new OnAnotherChangedMapValue();
    OnChangedMapValue* pl = new OnChangedMapValue();
    ChangedMapValue::notify(42);
    delete pl;

    new OnChangedMapValue();
    new OnChanged2MapValue();
    ChangedMapValue::notify(24);

    AnotherChangedMapValue::notify(12.22);

    //ListenerThread lt;
    ListenerThread *plt = new ListenerThread();
    delete plt;
    //lt.start();
    msleep(5);

/*
    arc_event_init();
    subscribe();

    for (int i = 0; i < 10; ++i) {
        storeMessage();
    }
    msleep(1000);

    unsubscribe();
    arc_event_free();
*/
    return 0;
}
