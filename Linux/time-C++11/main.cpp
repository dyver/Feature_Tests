// #include <iostream>
// #include <chrono>
// #include <thread>
// #include <unistd.h>
//
// std::chrono::seconds sleepingTime(2);
//
// void work() {
//     bool alive = true;
//     auto hardWorkThreadFunction = [&alive]() {
//         while (alive) {
//         }
//     };
//     auto threadFunction = [&alive]() {
//         std::this_thread::sleep_for(sleepingTime);
//         alive = false;
//     };
//     std::thread controlThread{threadFunction};
//     std::thread hardWorkThread{hardWorkThreadFunction};
//     controlThread.join();
//     hardWorkThread.join();
// }
//
// void work2() {
//     usleep(1000000);
// }
//
// int main() {
//     using SC = std::chrono::steady_clock;
//     std::chrono::time_point<SC> before = SC::now();
//     int sleepingTimeMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(sleepingTime).count();
//     std::cout << "specified time: " << sleepingTimeMilliseconds << "ms" << std::endl;
//     work();
//     std::chrono::time_point<SC> after = SC::now();
//     auto elapsed = after - before;
//     int elapsedMilliseconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
//     std::cout << "elapsed time: " << elapsedMilliseconds << "ms" << std::endl;
// }

#include <iostream>
#include <chrono>
#include <thread>

void f() {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

int main() {
    std::cout << "steady_clock is system_clock? " << (typeid(std::chrono::steady_clock) == typeid(std::chrono::system_clock)) << std::endl;
    using clock = std::chrono::system_clock;
    auto before = clock::now();
    std::cout << clock::to_time_t(before) << std::endl;
    f();
    auto after = clock::now();
    clock::duration duration = after - before;
    std::cout << typeid(clock).name() << std::endl;
    std::cout << typeid(duration).name() << std::endl;
    std::cout << "f() took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count()
              << " milliseconds\n";
}
