#include "Timer.h"

Timer::Timer(const std::string& taskName) : taskName(taskName) {
    start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << taskName << " took " << diff.count() << " seconds\n";
}
