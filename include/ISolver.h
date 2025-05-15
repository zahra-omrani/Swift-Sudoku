#pragma once
#include "Board.h"

class ISolver {
public:
    virtual bool solve(Board& b) = 0;
    virtual ~ISolver() = default;
};
