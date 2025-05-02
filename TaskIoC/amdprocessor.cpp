#include "amdprocessor.h"


void AMDProcessor::getProcessorInfo() const
{
    string typeStr = (getType() == x86) ? "x86" : "x64";
    std::cout << "Processor for" + getVersion() + std::to_string(getSpeed())+ "GHz " + typeStr;;
}
