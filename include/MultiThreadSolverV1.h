#pragma once

#ifndef MULTITHREADSOLVERV1_H
#define MULTITHREADSOLVERV1_H

#include "ISolver.h"
#include "Board.h"
#include <thread>
#include <atomic>

class MultiThreadSolverV1 : public ISolver {
public:
    bool solve(int board[9][9]) override;
    bool solve(Board& b) override;

private:
    bool isSafe(int board[9][9], int row, int col, int num);
    bool solveSudoku(int board[9][9]);
};

#endif // MULTITHREADSOLVERV1_H


/* we parallelize the isSafe() method using separate threads for row, column, and 3×3 box checks. Here's how we’ll approach it:
🔧 Key Changes in MultiThreadSolver (Version 1):
Spawn three threads:
One to check if the number is safe in the row.
One to check if the number is safe in the column.
One to check if the number is safe in the 3x3 box.
Combine their results to decide if a number is safe. */