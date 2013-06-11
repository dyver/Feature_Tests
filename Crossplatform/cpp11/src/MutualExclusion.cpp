#include <thread> // for std::thread
#include <mutex> // for std::mutex

#include <++cpp11.h>

// Mutual exclusion

void MutualExclusion() {
    // std::mutex
    const auto data_initial_value = 666;
    const auto threads_total = 20;
    const auto cycles_total = 1000;
    std::vector<std::thread*> threads;
    std::mutex mutex;
    int data = data_initial_value;
    auto misses_index = 0;
    auto f1 = [&data, &mutex]() {
        for (auto i = 0; i < cycles_total; ++i) {
            mutex.lock();
            ++data;
            mutex.unlock();
        }
    };
    auto f2 = [&data, &mutex]() {
        for (auto i = 0; i < cycles_total; ++i) {
            mutex.lock();
            --data;
            mutex.unlock();
        }
    };
    auto f3 = [&mutex, &misses_index]() {
        for (auto i = 0; i < cycles_total; ++i) {
            if (!mutex.try_lock()) {
                ++misses_index;
            } else {
                mutex.unlock();
            }
        }
    };
    std::timed_mutex timed_mutex;
    auto f4 = [&timed_mutex, &misses_index]() {
        for (auto i = 0; i < cycles_total; ++i) {
            if (!timed_mutex.try_lock_for(std::chrono::nanoseconds(1))) {
                ++misses_index;
            } else {
                timed_mutex.unlock();
            }
        }
    };
    auto f5 = [&timed_mutex, &misses_index]() {
        for (auto i = 0; i < cycles_total; ++i) {
            if (!timed_mutex.try_lock_for(std::chrono::nanoseconds(1))) {
                ++misses_index;
            } else {
                timed_mutex.unlock();
            }
        }
    };
    for (auto i = 0; i < threads_total; ++i) {
        threads.emplace_back(new std::thread(f1));
        threads.emplace_back(new std::thread(f2));
        threads.emplace_back(new std::thread(f3));
        threads.emplace_back(new std::thread(f4));
        threads.emplace_back(new std::thread(f5));
    }
    for (auto& i : threads) i->join();
    for (auto i : threads) delete i;
    threads.clear();
    outHeader("Mutual exclusion");
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
        << threads_total * cycles_total * 2
        << std::endl;
    // std::recursive_mutex
    data = data_initial_value;
    std::recursive_mutex recursive_mutex;
    struct S {
        std::recursive_mutex& mutex;
        int& data;
        int run_index;
        S(std::recursive_mutex& m, int& d) : mutex(m), data(d) { run_index = 0; }
        void fr() {
            mutex.lock();
            if (int(data / 2) * 2 == data) {
                ++data;
            } else {
                --data;
            }
            if (++run_index < 10) {
                fr();
            }
            mutex.unlock();
        }
        void operator ()() { fr(); }
    };
    for (auto i = 0; i < threads_total; ++i) {
        threads.emplace_back(new std::thread(S(recursive_mutex, data)));
    }
    for (auto& i : threads) i->join();
    for (auto i : threads) delete i;
    threads.clear();
    outIdent();
    std::cout
        << "shared data processed using recursive mutex value = "
        << data
        << std::endl;
}
