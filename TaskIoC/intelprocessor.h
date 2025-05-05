#ifndef INTELPROCESSOR_H
#define INTELPROCESSOR_H

#include "iprocessor.h"

class IntelProcessor : public IProcessor
{
private:
    string m_version;
    ProcessorType m_type;
    double m_speed;

public:
    IntelProcessor(): IntelProcessor("i7-12700K", ProcessorType::x64, 3.6){}

IntelProcessor(string version, ProcessorType type, double speed):
        m_version(version), m_type(type), m_speed(speed){}

string getVersion() const override{
    return m_version;
}

ProcessorType getType() const override{
    return m_type;
}

double getSpeed() const override{
    return m_speed;
}


void getProcessorInfo() const override;

};




#endif // INTELPROCESSOR_H
