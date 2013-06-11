#include <future> // for std::future and std::promise

#include <++cpp11.h>

// std::async();

void Async() {
    auto thread_function = []() -> int {
        const int IterationsTotal = 100000000;
        int result;
        for (int i = 0; i < IterationsTotal; ++i) ++result;
        return result;
    };
    typedef std::vector<std::unique_ptr<std::future<int>>> FC;
    FC futures;
    const int TasksTotal = 4;
    using namespace std::chrono;
    auto before = system_clock::now();
    for (auto i = 0; i < TasksTotal; ++i) {
        futures.emplace_back(new std::future<int>(std::async(thread_function)));
    }
    int result = 0;
    for (auto& i : futures) result += i->get();
    microseconds elapsed = duration_cast<microseconds>(system_clock::now() - before);
    outHeader("std::async()");
    outIdent();
    std::cout
        << "result = "
        << result
        << " elapsed = "
        << elapsed.count() << " microseconds"
        << " in " << TasksTotal << " threads";
    outTail();
}
