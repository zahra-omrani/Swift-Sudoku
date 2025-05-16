#include "MultiThreadSolverV2.h"
#include <thread>
#include <future>
#include <vector>
#include <algorithm>

bool MultiThreadSolverV2::solve(int board[9][9]) {
    return solveSudoku(board);
}

bool MultiThreadSolverV2::solve(Board& b) {
    int (*grid)[9] = b.getGrid();
    return solveSudoku(grid);
}

bool MultiThreadSolverV2::isSafe(int board[9][9], int row, int col, int num) {
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] == num || board[i][col] == num) return false;
    }
    int boxStartRow = row - row % 3;
    int boxStartCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[boxStartRow + i][boxStartCol + j] == num)
                return false;

    return true;
}

bool MultiThreadSolverV2::solveSudoku(int board[9][9]) {
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

    if (!emptyFound) return true; // Solved

    std::atomic<bool> solutionFound(false);
    std::vector<std::future<bool>> futures;

    for (int num = 1; num <= 9; ++num) {
        if (isSafe(board, row, col, num)) {
            int newBoard[9][9];
            std::copy(&board[0][0], &board[0][0] + 81, &newBoard[0][0]);
            newBoard[row][col] = num;

            futures.emplace_back(std::async(std::launch::async, [newBoard, &solutionFound, &board, this]() mutable {
                if (solutionFound.load()) return false;
                if (solveSudoku(newBoard)) {
                    if (!solutionFound.exchange(true)) {
                        std::copy(&newBoard[0][0], &newBoard[0][0] + 81, &board[0][0]);
                        return true;
                    }
                }
                return false;
            }));

        }
    }

    for (auto& f : futures) {
        if (f.get()) return true;
    }

    return false;
}
