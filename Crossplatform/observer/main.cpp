#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

namespace util
{
    template <int Id, class Data> class OnEventBase
    {
        public:
            OnEventBase()
            {
                storage.add(this);
            }
            virtual ~OnEventBase()
            {
cout << "~OnEventBase" << endl;
                storage.remove(this);
            }
            virtual void invoke(const Data& d) = 0;
            static void notify(const Data& d)
            {
                storage.notify(d);
            }
        private:
            class Storage
            {
                friend class OnEventBase<Id, Data>;
                void add(OnEventBase<Id, Data>* item)
                {
                    listeners.push_back(item);
                }
                void remove(OnEventBase<Id, Data>* item)
                {
                    if (destructing) return;
                    typename TL::iterator i = std::find(listeners.begin(), listeners.end(), item);
                    listeners.erase(i);
                }
                void notify(const Data& d)
                {
                    for (typename TL::iterator i = listeners.begin(); i != listeners.end(); ++i) {
                        (*i)->invoke(d);
                    }
                }
                Storage()
                {
                    destructing = false;
                }
                ~Storage()
                {
cout << "~Storage" << endl;
                    destructing = true;
                    for (typename TL::iterator i = listeners.begin(); i != listeners.end(); ++i) {
                        if (*i) delete *i;
                    }
                }
                typedef std::list<OnEventBase<Id, Data>*> TL;
                TL listeners;
                bool destructing;
            };
            static Storage storage;
    };
    template <int Id, class Data>
            typename util::OnEventBase<Id, Data>::Storage util::OnEventBase<Id, Data>::storage;
}

using namespace util;

// Событие

typedef OnEventBase<0, int> ChangedValue;

// Обозреваемый

void notify()
{
    ChangedValue::notify(42);
}

// Обозреватель

class OnChangedValue : public ChangedValue
{
    public:
        void invoke(const int& value);
};

void OnChangedValue::invoke(const int& value)
{
    cout << "Received message about changing value: " << value << endl;
}

int main()
{
    // Включаем прослушивание
    OnChangedValue* p = new OnChangedValue();
    // Оповещаем обозревателя
    notify();
    // Выключаем прослушивание
    delete p;
}