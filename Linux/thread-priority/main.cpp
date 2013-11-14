#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define CHECK(name) { \
    int ret = (name); \
    if (ret) { \
        std::cerr << "Error in " #name " = " << ret << std::endl; \
        return EXIT_FAILURE; \
    } \
}

void* task(void*) {
    for (int i = 0; i < 5; ++i) {
        usleep(100);
        cout << "Cycle # " << i << endl;
    }
    return 0;
}

int main() {

    pthread_t thread;
    pthread_attr_t attr;
    sched_param param;

    CHECK(pthread_attr_init(&attr));

    int minPriority = sched_get_priority_min(SCHED_RR);
    int maxPriority = sched_get_priority_max(SCHED_RR);
    cout << "MinPriority=" << minPriority << endl;
    cout << "MaxPriority=" << maxPriority << endl;

    param.sched_priority = 10;

    CHECK(pthread_attr_setschedpolicy(&attr, SCHED_RR));
    CHECK(pthread_attr_setschedparam(&attr, &param));
//    CHECK(pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED));

    CHECK(pthread_create(&thread, &attr, task, NULL));

    int policy;
    CHECK(pthread_getschedparam(thread, &policy, &param));

    std::cerr << "Priority: " << param.sched_priority << std::endl;

    CHECK(pthread_join(thread, NULL));

    CHECK(pthread_attr_destroy(&attr));

    return 0;
}
