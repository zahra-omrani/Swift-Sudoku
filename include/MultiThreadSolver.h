#ifndef MULTITHREADSOLVER_H
#define MULTITHREADSOLVER_H

#include "ISolver.h"
#include <vector>
#include <string>
#include <thread>

class MultiThreadSolver : public ISolver {
public:
    MultiThreadSolver(int threadCount = std::thread::hardware_concurrency());

    //This overrides ISolver's pure virtual function
    void solveBoards(const std::vector<std::string>& boards) override;

    //This is your custom version � DO NOT put override here
    void solveBoards(const std::vector<std::string>& boards, bool enableOutput);

private:
    int numThreads;
};

#endif
