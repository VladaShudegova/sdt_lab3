#ifndef AMDPROCESSOR_H
#define AMDPROCESSOR_H

#include "iprocessor.h"

class AMDProcessor : public IProcessor
{
private:
    string m_version;
    ProcessorType m_type;
    double m_speed;

public:

    AMDProcessor(){
        AMDProcessor("A6-9500E OEM", ProcessorType::x86, 3.0);
    }

    AMDProcessor(string version, ProcessorType type, double speed):
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



#endif // AMDPROCESSOR_H
