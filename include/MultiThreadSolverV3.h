#pragma once
#include "Board.h"
#include <atomic>

class MultiThreadSolverV3 {
public:
    bool solve(int board[9][9]);
    bool solve(Board& b);

    static std::atomic<int> activeThreads;
    static std::atomic<int> maxThreadsObserved;

private:
    bool solveSudoku(int board[9][9], int depth);
    bool isSafe(int board[9][9], int row, int col, int num);

    static constexpr int MAX_PARALLEL_DEPTH = 1; // adjust if needed

};
