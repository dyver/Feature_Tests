#include <condition_variable> // for std::condition_variable
#include <chrono> // for time utilities
#include <thread> // for std::thread and std::this_thread
#include <mutex> // for std::mutex, std::unique_lock and std::lock_guard
#include <queue> // for std::queue

#include <++c.h>

// Condition variables

struct Message {
    Message(int ii) : i{ii} {}
    int i = 0;
};

void ConditionVariables() {
    const int Times = 10;

    std::mutex mutex;
    std::queue<Message> queue;
    std::condition_variable condition_variable;

    auto consumer = [&]() {
        while (true) {
            std::unique_lock<std::mutex> ul{mutex};
            condition_variable.wait(ul);
            while (queue.size()) {
                auto m = queue.front();
                queue.pop();
                outIdent();
                std::cout << "Message: " << m.i << std::endl;
                if (m.i == Times - 1) {
                    return;
                }
            }
        }
    };

    auto producer = [&]() {
        for (auto i = 0; i < Times; ++i) {
            {
                Message m{i};
                std::lock_guard<std::mutex> lg{mutex};
                queue.push(m);
                condition_variable.notify_one();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds{100});
        }
    };

    outHeader("Condition variables");

    std::thread producer_thread{producer};
    std::thread consumer_thread{consumer};
    producer_thread.join();
    consumer_thread.join();

    outTail();
}
