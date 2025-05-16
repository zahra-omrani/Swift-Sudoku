#pragma once
#include "Board.h"

class MultiThreadSolverV3 {
public:
    bool solve(int board[9][9]);
    bool solve(Board& b);

private:
    static const int MAX_PARALLEL_DEPTH = 2; // control how deep parallelism goes
    bool solveSudoku(int board[9][9], int depth);
    bool isSafe(int board[9][9], int row, int col, int num);
};
