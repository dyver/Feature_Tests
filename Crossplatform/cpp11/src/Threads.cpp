#include <thread> // for std::thread
#include <mutex> // for std::mutex

#include <++cpp11.h>

// Threads

void Threads() {
    try {
        std::mutex mutex;
        const int times = 1000000;
        // data shared between threads
        typedef std::shared_ptr<int> SD;
        SD data(new int());
        *data = 0;
        // lambda function
        auto lf = [data, &mutex]() {
            for (auto i = 0; i < times; ++i) {
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
            void operator ()() {
                for (auto i = 0; i < times; ++i) {
                    mutex.lock();
                    --*data;
                    mutex.unlock();
                }
            }
        };
        // lambda function with argument
        auto lfa = [](SD data, std::mutex& mutex) {
            for (auto i = 0; i < times; ++i) {
                mutex.lock();
                --*data;
                mutex.unlock();
            }
        };
        // making and starting threads
        std::thread th1{lf};
        std::thread th2{Sf(data, mutex)};
        //std::thread th3{std::bind(lfa, data, mutex)}; // can't bind mutex
        // do some work in main thread
        lfa(data, mutex);
        // waiting for threads ending
        th1.join();
        th2.join();
        outHeader("Threads & mutexes");
        outIdent();
        std::cout << "shared data = " << *data << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception" << e.what() << std::endl;
    }
}
