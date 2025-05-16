#include "MultiThreadSolverV1.h"
#include <iostream>

bool MultiThreadSolverV1::solve(int board[9][9]) {
    return solveSudoku(board);
}

bool MultiThreadSolverV1::solve(Board& b) {
    int (*grid)[9] = b.getGrid();
    return solveSudoku(grid);
}

bool MultiThreadSolverV1::isSafe(int board[9][9], int row, int col, int num) {
    std::atomic<bool> rowSafe(true), colSafe(true), boxSafe(true);

    std::thread rowThread([&]() {
        for (int i = 0; i < 9; ++i) {
            if (board[row][i] == num) {
                rowSafe = false;
                break;
            }
        }
    });

    std::thread colThread([&]() {
        for (int i = 0; i < 9; ++i) {
            if (board[i][col] == num) {
                colSafe = false;
                break;
            }
        }
    });

    std::thread boxThread([&]() {
        int boxStartRow = row - row % 3;
        int boxStartCol = col - col % 3;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[boxStartRow + i][boxStartCol + j] == num) {
                    boxSafe = false;
                    return;
                }
            }
        }
    });

    rowThread.join();
    colThread.join();
    boxThread.join();

    return rowSafe && colSafe && boxSafe;
}

bool MultiThreadSolverV1::solveSudoku(int board[9][9]) {
    int row, col;

    // Find empty cell
    bool emptyFound = false;
    for (row = 0; row < 9 && !emptyFound; ++row) {
        for (col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                emptyFound = true;
                break;
            }
        }
    }

    if (!emptyFound) return true; // No empty cells

    --row; // Adjust row after loop

    for (int num = 1; num <= 9; ++num) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board))
                return true;
            board[row][col] = 0;
        }
    }

    return false;
}
