#ifndef CALLBACK_HPP
#define CALLBACK_HPP

// Callback system management

#include <list>
#include <algorithm>

namespace callback
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
                storage.remove(this);
            }
            virtual void invoke(const Data& d) = 0;
            static void notify(const Data& d)
            {
                storage.notify(d);
            }
        private:
            class Storage {
                friend class OnEventBase<Id, Data>;
                void add(OnEventBase<Id, Data>* item) {
                    listeners.push_back(item);
                }
                void remove(OnEventBase<Id, Data>* item) {
                    if (destructing) return;
                    typename TL::iterator i = std::find(listeners.begin(), listeners.end(), item);
                    listeners.erase(i);
                }
                void notify(const Data& d) {
                    for (typename TL::iterator i = listeners.begin(); i != listeners.end(); ++i)
                    (*i)->invoke(d);
                }
                Storage() { destructing = false; }
                ~Storage() {
                    destructing = true;
                    for (typename TL::iterator i = listeners.begin(); i != listeners.end(); ++i)
                        if (*i) delete *i;
                }
                typedef std::list<OnEventBase<Id, Data>*> TL;
                TL listeners;
                bool destructing;
            };

            static Storage storage;
    };

    template <int Id, class Data>
            typename callback::OnEventBase<Id, Data>::Storage callback::OnEventBase<Id, Data>::storage;
}

#endif // CALLBACK_HPP
