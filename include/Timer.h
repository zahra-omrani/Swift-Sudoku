#pragma once

#include <chrono>
#include <string>
#include <iostream>

class Timer {
public:
    Timer();  // Default constructor
    explicit Timer(const std::string& taskName);  // Named constructor

    void start();
    void stop();
    long long elapsedMilliseconds() const;
    double elapsedSeconds() const;

    ~Timer();  // Only logs if taskName is given

private:
    std::string taskName;
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    bool stopped = false;
    bool hasTaskName = false;
};
