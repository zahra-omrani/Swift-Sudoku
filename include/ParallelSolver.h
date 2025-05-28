#ifndef PARALLELSOLVER_H
#define PARALLELSOLVER_H

#include <vector>
#include <string>

class ParallelSolver {
public:
    void solveBoards(const std::vector<std::string>& boards, int threadCount);
};

#endif // PARALLELSOLVER_H
