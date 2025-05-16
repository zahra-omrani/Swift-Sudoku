#pragma once

#ifndef ISOLVER_H
#define ISOLVER_H

#include "Board.h"

class ISolver {
public:
    virtual bool solve(int board[9][9]) = 0;
    virtual bool solve(Board& b) = 0;
    virtual ~ISolver() = default;
};

#endif // ISOLVER_H
