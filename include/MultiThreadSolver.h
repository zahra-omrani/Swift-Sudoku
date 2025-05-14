#ifndef MULTITHREADVALIDATOR_HPP
#define MULTITHREADVALIDATOR_HPP

#include "IValidator.hpp"
#include <thread>
#include <vector>

class MultiThreadValidator : public IValidator {
public:
    bool validate(const Board& b) override;

private:
    bool validateRowsParallel(const Board& b);
    bool validateColsParallel(const Board& b);
    bool validateBoxesParallel(const Board& b);
};

#endif // MULTITHREADVALIDATOR_HPP
