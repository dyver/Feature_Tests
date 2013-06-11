#include <future> // for std::future and std::promise

#include <++cpp11.h>

// std::future and std::promise

void FutureAndPromise() {
    // data to process
    const int DataSize = 100000000;
    typedef std::vector<int> DataType;
    DataType data(DataSize);
    for (auto& i : data) i = 2;
    // data parts for tasks
    typedef std::pair<int, int> DiapType;
    typedef std::vector<std::unique_ptr<DiapType>> DC;
    DC diapasons;
    // function to be executed to process data
    auto thread_function = [](int* data, const DiapType& diapason) -> int {
        int result = 0;
        for (int i = diapason.first; i <= diapason.second; ++i) {
            result += *(data + i);
        }
        return result;
    };
    // parallel tasks
    typedef std::packaged_task<int (int*, const DiapType&)> TaskType;
    typedef std::vector<std::unique_ptr<TaskType>> TC;
    TC tasks;
    // futures from tasks
    typedef std::future<int> FutureType;
    typedef std::vector<std::unique_ptr<FutureType>> FC;
    FC futures;
    // constructing tasks, futures and diapasons
    const int TasksTotal = 4;
    for (auto i = 0; i < TasksTotal; ++i) {
        tasks.emplace_back(new TaskType(thread_function));
        futures.emplace_back(new FutureType(tasks.back()->get_future()));
        int part = DataSize / TasksTotal;
        diapasons.emplace_back(new DiapType(part * i, part * (i + 1) - 1));
    }
    using namespace std::chrono;
    auto before = system_clock::now();
    // executing tasks
    for (auto i = 0; i < TasksTotal; ++i) {
        tasks[i]->operator()(&data[0], *diapasons[i]);
    }
    // waiting(!) for result
    int result = 0;
    for (auto& i : futures) result += i->get();
    nanoseconds elapsed = system_clock::now() - before;
    outHeader("std::future and std::promise");
    outIdent();
    std::cout
        << "result = "
        << result
        << " elapsed = "
        << elapsed.count() << " microseconds"
        << " in " << TasksTotal << " threads"
        << std::endl;
}
