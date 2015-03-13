#include <thread> // for std::thread
#include <mutex> // for std::mutex

#include <++c.h>

// Threads

using SD = std::shared_ptr<int>;

static const int Times = 1000000;

// standalone task function
void taskFunction(SD data, std::mutex& mutex) {
    for (auto i = 0; i < Times; ++i) {
        mutex.lock();
        ++*data;
        mutex.unlock();
    }
}

void Threads() {
    try {
        std::mutex mutex;
        // data shared between threads
        // note, that we can pass this wrapped data by value or reference due to shared_ptr
        SD data(new int());
        // we will have 5 threads doing equal opposite work, so initial value must be -Times
        // to yeld in a 0
        *data = -Times;
        // lambda function with closured data
        auto lf = [data, &mutex]() {
            for (auto i = 0; i < Times; ++i) {
                mutex.lock();
                --*data;
                mutex.unlock();
            }
        };
        // lambda function with data passed throw argument
        auto lfa = [](SD data, std::mutex& mutex) {
            for (auto i = 0; i < Times; ++i) {
                mutex.lock();
                ++*data;
                mutex.unlock();
            }
        };
        // inner struct functional object
        struct Sf {
            SD& data;
            std::mutex &mutex;
            Sf(SD& d, std::mutex& m) : data(d), mutex(m) {}
            void operator()() {
                for (auto i = 0; i < Times; ++i) {
                    mutex.lock();
                    --*data;
                    mutex.unlock();
                }
            }
        };
        outHeader("Threads & mutexes");
        outIdent();
        std::cout << "initial value of shared data = " << *data << std::endl;
        outIdent();
        std::cout << "doing work in 5 threads ..." << std::flush;
        // making and starting threads
        std::thread th1{taskFunction, data, std::ref(mutex)};
        std::thread th2{lf};
        std::thread th3{Sf(data, mutex)};
        std::thread th4{std::bind(lfa, data, std::ref(mutex))};
        // do some work in main thread
        lfa(data, mutex);
        // waiting for threads ending
        th1.join();
        th2.join();
        th3.join();
        th4.join();
        std::cout << " done." << std::endl;
        outIdent();
        std::cout << "processed shared data = " << *data << " (must be = 0)" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception" << e.what() << std::endl;
    }
}
