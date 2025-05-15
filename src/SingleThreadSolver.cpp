#include "SingleThreadSolver.h"

bool SingleThreadSolver::solve(Board& b) {
    return solveRecursive(b, 0, 0);
}

bool SingleThreadSolver::solveRecursive(Board& b, int row, int col) {
    if (row == 9) return true;
    if (col == 9) return solveRecursive(b, row + 1, 0);
    if (b.at(row, col) != 0) return solveRecursive(b, row, col + 1);

    for (int num = 1; num <= 9; ++num) {
        if (isValid(b, row, col, num)) {
            b.set(row, col, num);
            if (solveRecursive(b, row, col + 1)) return true;
            b.set(row, col, 0);
        }
    }
    return false;
}

bool SingleThreadSolver::isValid(const Board& b, int row, int col, int num) {
    for (int i = 0; i < 9; ++i) {
        if (b.at(row, i) == num || b.at(i, col) == num) return false;
    }
    int r = row - row % 3, c = col - col % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (b.at(r + i, c + j) == num) return false;
    return true;
}
