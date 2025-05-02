#include "intelprocessor.h"



void IntelProcessor::getProcessorInfo() const
{
    string typeStr = (this->getType() == x86) ? "x86" : "x64";
    std::cout << "Processor for " + this->getVersion() +" "+ std::to_string(this->getSpeed())+ "GHz " + typeStr << "\n";
}
