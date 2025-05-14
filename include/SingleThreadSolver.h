#ifndef SINGLETHREADVALIDATOR_HPP
#define SINGLETHREADVALIDATOR_HPP

#include "IValidator.hpp"

class SingleThreadValidator : public IValidator {
public:
    bool validate(const Board& b) override;

private:
    bool checkRows(const Board& b);
    bool checkCols(const Board& b);
    bool checkBoxes(const Board& b);
};

#endif // SINGLETHREADVALIDATOR_HPP
