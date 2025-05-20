#pragma once
#include <chrono>

class Timer {
public:
    void start();
    void stop();
    double elapsedMilliseconds() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;
};
