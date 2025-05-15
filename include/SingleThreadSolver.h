#pragma once
#include "ISolver.h"

class SingleThreadSolver : public ISolver {
public:
    bool solve(Board& b) override;
private:
    bool solveRecursive(Board& b, int row, int col);
    bool isValid(const Board& b, int row, int col, int num);
};
