#include "SingleThreadSolver.h"

bool SingleThreadSolver::solve(int board[9][9]) {
    return solveSudoku(board);
}

bool SingleThreadSolver::solve(Board& b) {
    int (*grid)[9] = b.getGrid();
    return solveSudoku(grid);
}

bool SingleThreadSolver::isSafe(int board[9][9], int row, int col, int num) {
    // Check row and column
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    // Check 3x3 subgrid
    int boxStartRow = row - row % 3;
    int boxStartCol = col - col % 3;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[boxStartRow + i][boxStartCol + j] == num)
                return false;

    return true;
}

bool SingleThreadSolver::solveSudoku(int board[9][9]) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isSafe(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board))
                            return true;
                        board[row][col] = 0; // backtrack
                    }
                }
                return false; // no number fits here
            }
        }
    }
    return true; // solved
}
