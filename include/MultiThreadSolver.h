#ifndef MULTITHREADSOLVER_H
#define MULTITHREADSOLVER_H

#include "ISolver.h"
#include <vector>
#include <string>
#include <thread>

class MultiThreadSolver : public ISolver {
public:
    MultiThreadSolver(int threadCount = std::thread::hardware_concurrency());
    void solveBoards(const std::vector<std::string>& boards) override;

private:
    int numThreads;
};

#endif
