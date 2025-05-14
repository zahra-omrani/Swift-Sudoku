#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <string>
#include <iostream>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::string task;

public:
    Timer(const std::string& taskName);
    ~Timer();
};

#endif // TIMER_HPP
