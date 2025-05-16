#include "MultiThreadSolverV3.h"
#include <future>
#include <vector>
#include <algorithm>
#include <iostream> // optional for debug

// Initialize static atomic counters
std::atomic<int> MultiThreadSolverV3::activeThreads{0};
std::atomic<int> MultiThreadSolverV3::maxThreadsObserved{0};

MultiThreadSolverV3::MultiThreadSolverV3(int maxThreads_) : maxThreads(maxThreads_) {}

bool MultiThreadSolverV3::solve(int board[9][9]) {
    activeThreads = 1; // main thread counts as active
    maxThreadsObserved = 1;

    bool result = solveSudoku(board, 0);

    activeThreads = 0;
    return result;
}

bool MultiThreadSolverV3::solve(Board& b) {
    int (*grid)[9] = b.getGrid();

    activeThreads = 1;
    maxThreadsObserved = 1;

    bool result = solveSudoku(grid, 0);

    activeThreads = 0;
    return result;
}

bool MultiThreadSolverV3::isSafe(int board[9][9], int row, int col, int num) {
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    int boxStartRow = row - row % 3;
    int boxStartCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[boxStartRow + i][boxStartCol + j] == num)
                return false;

    return true;
}

bool MultiThreadSolverV3::solveSudoku(int board[9][9], int depth) {
    int row = -1, col = -1;
    bool emptyFound = false;

    for (int i = 0; i < 9 && !emptyFound; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == 0) {
                row = i;
                col = j;
                emptyFound = true;
                break;
            }
        }
    }

    if (!emptyFound)
        return true;

    std::atomic<bool> solutionFound(false);
    std::vector<std::future<bool>> futures;

    for (int num = 1; num <= 9; ++num) {
        if (isSafe(board, row, col, num)) {
            int newBoard[9][9];
            std::copy(&board[0][0], &board[0][0] + 81, &newBoard[0][0]);
            newBoard[row][col] = num;

            // Check if we can spawn a new thread:
            if (depth < MAX_PARALLEL_DEPTH && activeThreads.load() < maxThreads) {
                activeThreads++;
                int currentActive = activeThreads.load();
                int oldMax = maxThreadsObserved.load();
                while (currentActive > oldMax && !maxThreadsObserved.compare_exchange_weak(oldMax, currentActive)) {
                    // try to update maxThreadsObserved
                }

                futures.emplace_back(std::async(std::launch::async, [newBoard, depth, &solutionFound, &board, this]() mutable {
                    if (solutionFound.load()) {
                        activeThreads--;
                        return false;
                    }
                    bool res = solveSudoku(newBoard, depth + 1);
                    if (res) {
                        if (!solutionFound.exchange(true)) {
                            std::copy(&newBoard[0][0], &newBoard[0][0] + 81, &board[0][0]);
                        }
                    }
                    activeThreads--;
                    return res;
                }));
            } else {
                // fallback to serial recursion if max threads reached
                board[row][col] = num;
                if (solveSudoku(board, depth + 1))
                    return true;
                board[row][col] = 0;
            }
        }
    }

    for (auto& f : futures) {
        if (f.get())
            return true;
    }

    return false;
}
