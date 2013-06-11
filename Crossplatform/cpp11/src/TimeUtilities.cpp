#include <chrono> // for time utilities

#include <++cpp11.h>

// Time utilities

void TimeUtilities() {
    auto work = []() {
        const auto repeats = 10000000;
        for (auto r = 0; r < repeats; ++r) {
            int i = 0;
            int j = i;
            int k = j;
            i = k;
        }
    };
    using namespace std::chrono;
    system_clock::time_point before = system_clock::now();
    work();
    system_clock::duration elapsed = system_clock::now() - before;
    outHeader("Time utilities");
    outIdent();
    std::cout
        << "system_clock : elapsed = "
        << elapsed.count() << " ticks"
        << std::endl;
    auto hrnow = high_resolution_clock::now();
    work();
    microseconds hrduration = duration_cast<microseconds>(high_resolution_clock::now() - hrnow);
    outIdent();
    std::cout
        << "high resolution clock : elapsed = "
        << hrduration.count() << " microseconds"
        << std::endl;
    duration<long> durationSeconds(42);
    duration<long, std::kilo> durationKiloSeconds(42);
    nanoseconds nanoSeconds(42);
    microseconds microSeconds(42);
    milliseconds milliSeconds(42);
    seconds Seconds(42);
    minutes Minutes(42);
    hours Hours(42);
    outIdent();
    std::cout
        << "some useful definitions : "
        << durationSeconds.count() << " long seconds "
        << durationKiloSeconds.count() << " kiloseconds "
        << nanoSeconds.count() << " nanoseconds "
        << microSeconds.count() << " microseconds "
        << milliSeconds.count() << " milliseconds "
        << Seconds.count() << " seconds "
        << Minutes.count() << " minutes "
        << Hours.count() << " hours "
        << std::endl;
}
