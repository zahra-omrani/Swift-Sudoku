#pragma once
#include <chrono>
#include <string>
#include <iostream>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start;
    std::string taskName;
public:
    Timer(const std::string& taskName);
    ~Timer();
};
