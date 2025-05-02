#ifndef ICOMPUTER_H
#define ICOMPUTER_H


#include <memory>
#include "iprocessor.h"

using std::shared_ptr;

class IComputer
{
public:
    virtual ~IComputer() = default;
    virtual void getComputer()const = 0;

};

#endif // ICOMPUTER_H
