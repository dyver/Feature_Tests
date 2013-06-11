#include "parallel.hpp"

#include <iostream>

using namespace parallel;

Mutex coutMutex;

namespace parallel
{
    class Registrator
    {
        public:
            Registrator() {}
            ~Registrator()
            {
                for (typename TL::iterator i = objects.begin(); i != objects.end(); ++i) {
                    (*i)->stop();
                    delete *i;
                }
            }
            void start(Thread* obj)
            {
                objects.insert(obj);
                obj->do_start();
                { MutexLocker ml(coutMutex);
                    std::cout << "Количество зарегистрированных объектов:" << objects.size() << std::endl;
                }
            }
            void destroy(Thread* obj)
            {
                obj->stop();
                typename TL::iterator i = objects.find(obj);
                if (i != objects.end()) {
                    delete *i;
                    objects.erase(i);
                } else {
                    delete obj;
                }
            }
        private:
            typedef std::set<Thread*> TL;
            TL objects;
    };
}

Thread::RPT Thread::registrator;

Thread::Thread(const std::string& n)
        : handle(0), name(n)
{
    if (!registrator.get()) registrator.reset(new Registrator);
}

void Thread::start()
{
    registrator->start(this);
}

void Thread::stop()
{
    if (!handle) return;
    { MutexLocker ml(coutMutex);
        std::cout << "Ожидаем завершения ..." << std::endl;
    }
    pthread_join(handle, 0);
    handle = 0;
    { MutexLocker ml(coutMutex);
        std::cout << "Присоединились" << std::endl;
    }
}

void Thread::destroy(Thread* th)
{
    registrator->destroy(th);
}

void Thread::do_start()
{
    if (handle) return;
    pthread_create(&handle, 0, &Thread::execute, this);
}

void* Thread::execute(void* arg)
{
    Thread* pthread = static_cast<Thread*>(arg);
    { MutexLocker ml(coutMutex);
        std::cout << "Запущен поток " << pthread->name << std::endl;
    }
    pthread->run();
    { MutexLocker ml(coutMutex);
        std::cout << "Завершился поток " << pthread->name << std::endl;
    }
    pthread_exit(0);
    return 0;
}


