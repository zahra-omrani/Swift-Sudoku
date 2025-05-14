#ifndef IVALIDATOR_HPP
#define IVALIDATOR_HPP

#include "Board.hpp"

class IValidator {
public:
    virtual ~IValidator() = default;
    virtual bool validate(const Board& b) = 0;
};

#endif // IVALIDATOR_HPP
