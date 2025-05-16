#ifndef SEQUENTIALSOLVER_H
#define SEQUENTIALSOLVER_H

#include "ISolver.h"

class SequentialSolver : public ISolver {
public:
    bool solve(int board[9][9]) override;
    bool solve(Board& b) override;

private:
    bool isSafe(int board[9][9], int row, int col, int num);
    bool solveSudoku(int board[9][9]);
};

#endif // SEQUENTIALSOLVER_H
