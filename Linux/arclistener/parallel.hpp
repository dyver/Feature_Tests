#ifndef PARALLEL_HPP
#define PARALLEL_HPP

#include <string>
#include <pthread.h>

namespace parallel
{
    class Mutex
    {
        public:
            Mutex() { pthread_mutex_init(&handle, 0); }
            virtual ~Mutex() { unlock(); pthread_mutex_destroy(&handle); }
            void lock() { pthread_mutex_lock(&handle); }
            void unlock() { pthread_mutex_unlock(&handle); }
        protected:
            pthread_mutex_t handle;
    };

    class MutexLocker
    {
        public:
            MutexLocker(Mutex& m) : mutex(m) { mutex.lock(); }
            ~MutexLocker() { mutex.unlock(); }
        private:
            Mutex& mutex;
    };

    Mutex coutMutex;

    class Thread
    {
        public:
            Thread(const std::string& n = "", bool startNow = false)
                    : handle(0), name(n), constructed(false)
            {
                if (startNow) start();
            }
            virtual ~Thread()
            {
                stop();
            }
            void start()
            {
                pthread_create(&handle, 0, &Thread::execute, this);
            }
            void stop()
            {
                if (handle) {
                    { MutexLocker ml(coutMutex);
                        std::cout << "~Thread" << std::endl;
                    }
                    pthread_join(handle, 0);
                    handle = 0;
                    { MutexLocker ml(coutMutex);
                        std::cout << "Присоединились" << std::endl;
                    }
                }
            }
            //static void operator delete(void* p) { std::cout << "delete" << std::endl; }
        protected:
            virtual void run() = 0;
            pthread_t handle;
            std::string name;
            bool constructed;
        private:
            static void* execute(void* arg)
            {
                Thread* pthread = static_cast<Thread*>(arg);
                { MutexLocker ml(coutMutex);
                    std::cout << "Запущен поток " << pthread->name << std::endl;
                }
                if (pthread->constructed) pthread->run();
                { MutexLocker ml(coutMutex);
                    std::cout << "Завершился поток " << pthread->name << std::endl;
                }
                return 0;
            }
    };
}

#endif // PARALLEL_HPP
