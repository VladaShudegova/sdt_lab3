#ifndef IPROCESSOR_H
#define IPROCESSOR_H

#include <string>
#include <memory>
#include <iostream>

using std::string;

enum ProcessorType
{ x86,
  x64
};

class IProcessor
{
public:
    virtual ~IProcessor() = default;
    virtual void getProcessorInfo() const = 0;
    virtual string getVersion() const = 0;
    virtual ProcessorType getType() const = 0;
    virtual double getSpeed() const = 0;

};

#endif // IPROCESSOR_H
