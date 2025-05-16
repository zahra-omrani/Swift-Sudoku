#pragma once
#include "Board.h"
#include <atomic>

class MultiThreadSolverV3 {
public:
    MultiThreadSolverV3(int maxThreads = 14); // default max threads

    bool solve(int board[9][9]);
    bool solve(Board& b);

private:
    bool solveSudoku(int board[9][9], int depth);
    bool isSafe(int board[9][9], int row, int col, int num);

    int maxThreads; // user-specified max threads

    static std::atomic<int> activeThreads;
    static std::atomic<int> maxThreadsObserved;

    static constexpr int MAX_PARALLEL_DEPTH = 1; // control parallel recursion depth
};
