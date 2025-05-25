#ifndef ISOLVER_H
#define ISOLVER_H

#include <vector>
#include <string>

class ISolver {
public:
    virtual ~ISolver() = default;
    virtual void solveBoards(const std::vector<std::string>& boards) = 0;
};

#endif
