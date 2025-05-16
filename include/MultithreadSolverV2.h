#pragma once

#ifndef MULTITHREADSOLVERV2_H
#define MULTITHREADSOLVERV2_H

#include "ISolver.h"
#include "Board.h"
#include <atomic>
#include <future>
#include <vector>

class MultiThreadSolverV2 : public ISolver {
public:
    bool solve(int board[9][9]) override;
    bool solve(Board& b) override;

private:
    bool isSafe(int board[9][9], int row, int col, int num);
    bool solveSudoku(int board[9][9]);
};

#endif
