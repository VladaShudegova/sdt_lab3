#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include "icomputer.h"



class Computer : public IComputer
{

private:
    shared_ptr<IProcessor> m_processor;
    string m_superInfo;

public:

        Computer(shared_ptr<IProcessor> processor, string sInfo = "Computer has ")
        : m_processor(processor)
        , m_superInfo(sInfo){}


    void getComputer() const override
    {
        std::cout << m_superInfo<< ":\n";
        std::cout << "1.";
        m_processor->getProcessorInfo();
    }
};

#endif // COMPUTER_H
