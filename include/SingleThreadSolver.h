#pragma once
#include "ISolver.h"

class SingleThreadSolver : public ISolver {
public:
    bool solve(int board[9][9]) override;
    bool solve(Board& b) override;

private:
    bool solveSudoku(int board[9][9]);
    bool isSafe(int board[9][9], int row, int col, int num);
};
