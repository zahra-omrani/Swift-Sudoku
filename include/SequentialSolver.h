#ifndef SEQUENTIALSOLVER_H
#define SEQUENTIALSOLVER_H

#include "ISolver.h"

class SequentialSolver : public ISolver {
public:
    void solveBoards(const std::vector<std::string>& boards) override;
};

#endif
