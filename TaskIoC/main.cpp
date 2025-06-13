#include <QCoreApplication>
#include <iostream>

#include "ioc/iocconteiner.h"
#include "iprocessor.h"
#include "intelprocessor.h"
#include "amdprocessor.h"
#include "computer.h"


using std::cout;



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IOCContainer conteiner;


    conteiner.registerInstance<IProcessor, IntelProcessor>();

    auto processorInstance = conteiner.getObject<IProcessor>();
    processorInstance->getProcessorInfo();


    conteiner.registerInstance<IProcessor, AMDProcessor>();
    processorInstance = conteiner.getObject<IProcessor>();
    processorInstance->getProcessorInfo();

    std::cout<< "\n";
    conteiner.registerFactory<IComputer, Computer, IProcessor>();

    conteiner.getObject<IProcessor>()->getProcessorInfo();
    std::cout<< "\n";
    conteiner.getObject<IComputer>()->getComputer();





    return a.exec();
}
