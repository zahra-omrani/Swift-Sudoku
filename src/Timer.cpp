#include "Timer.h"

Timer::Timer() {
    // Empty constructor
}

Timer::Timer(const std::string& taskName) : taskName(taskName), hasTaskName(true) {
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::start() {
    stopped = false;
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    endTime = std::chrono::high_resolution_clock::now();
    stopped = true;
}

long long Timer::elapsedMilliseconds() const {
    auto endPoint = stopped ? endTime : std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(endPoint - startTime).count();
}

double Timer::elapsedSeconds() const {
    auto endPoint = stopped ? endTime : std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(endPoint - startTime).count();
}

Timer::~Timer() {
    if (hasTaskName) {
        stop();
        std::cout << taskName << " took " << elapsedSeconds() << " seconds\n";
    }
}
