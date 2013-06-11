#include <thread> // for std::thread
#include <mutex> // for std::mutex and std::***lock

#include <++cpp11.h>

// Locks

// WARNING: Unordered lock don't work on Windows

void Locks() {
    const auto data_initial_value = 666;
    const auto threads_total = 20;
    const auto cycles_total = 1000;
    typedef std::unique_lock<std::mutex> UL;
    typedef std::vector<std::unique_ptr<std::thread>> TC;
    TC threads;
    std::mutex mutex;
    std::mutex mutex1;
    std::mutex mutex2;
    std::mutex mutex3;
    int data = data_initial_value;
    int data1 = data_initial_value;
    int data2 = data_initial_value;
    int data3 = data_initial_value;
    auto misses_index = 0;
    auto f1 = [&data, &mutex]() {
        for (auto i = 0; i < cycles_total; ++i) {
            UL lock(mutex);
            ++data;
        }
    };
    auto f2 = [&data, &mutex, &misses_index]() {
        for (auto i = 0; i < cycles_total; ++i) {
            UL lock(mutex, std::defer_lock);
            if (lock.try_lock())
                --data;
            else
                ++misses_index;
        }
    };
    auto f3 = [&data1, &data2, &data3, &mutex1, &mutex2, &mutex3]() {
        for (auto i = 0; i < cycles_total; ++i) {
            UL lock1(mutex1, std::defer_lock);
            UL lock2(mutex2, std::defer_lock);
            UL lock3(mutex3, std::defer_lock);
            std::lock(lock1, lock2, lock3); // prevents deadlocks
            ++data1;
            ++data2;
            ++data3;
        }
    };
    auto f4 = [&data1, &data2, &data3, &mutex1, &mutex2, &mutex3]() {
        for (auto i = 0; i < cycles_total; ++i) {
            UL lock1(mutex1, std::defer_lock);
            UL lock2(mutex2, std::defer_lock);
            UL lock3(mutex3, std::defer_lock);
            // prevents deadlocks - note reverse order
            // WARNING: Unordered lock don't work on Windows
            //std::lock(lock3, lock2, lock1);
            std::lock(lock1, lock2, lock3);
            --data1;
            --data2;
            --data3;
        }
    };
    for (auto i = 0; i < threads_total; ++i) {
        threads.emplace_back(new std::thread(f1));
        threads.emplace_back(new std::thread(f2));
        threads.emplace_back(new std::thread(f3));
        threads.emplace_back(new std::thread(f4));
    }
    for (auto& i : threads) i->join();
    // now threads will be deleted automatically cause of unique_ptr property
    outHeader("Locks");
    outIdent();
    std::cout
        << "shared data initial value = "
        << data_initial_value
        << std::endl;
    outIdent();
    std::cout
        << "shared data processed value = "
        << data
        << std::endl;
    outIdent();
    std::cout
        << "shared data can't be locked for a "
        << misses_index
        << " times must be in range 0 - "
        << threads_total * cycles_total
        << std::endl;
    outIdent();
    std::cout
        << "processed value for shared data1 = "
        << data1
        << " and data2 = "
        << data2
        << " and data3 = "
        << data3
        << std::endl;
}
