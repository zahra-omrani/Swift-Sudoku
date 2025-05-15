#pragma once
#include "ISolver.h"
#include <future>
#include <vector>

class MultiThreadSolver : public ISolver {
public:
    bool solve(Board& b) override;
private:
    bool solveRecursive(Board b, int row, int col); // Pass-by-value for thread safety
    bool isValid(const Board& b, int row, int col, int num);
};
