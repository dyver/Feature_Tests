#ifndef PARALLEL_HPP
#define PARALLEL_HPP

#include <string>
#include <pthread.h>
#include <set>
#include <memory>

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

    class Registrator;
    template <typename T> class Thread<T>
    {
        public:
            Thread(const std::string& n = "");
            void start();
            void stop();
            static void destroy(Thread* th);
        private:
            virtual ~Thread() {}
            friend class Registrator;
            void do_start();
            static void* execute(void* arg);
            pthread_t handle;
            std::string name;
            typedef std::auto_ptr<Registrator> RPT;
            static RPT registrator;
    };
}

#endif // PARALLEL_HPP
