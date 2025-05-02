#include <QCoreApplication>
#include <iostream>

#include "iocconteiner.h"
#include "iprocessor.h"
#include "intelprocessor.h"
#include "amdprocessor.h"
#include "computer.h"


using std::cout;

class IAmAThing
{
public:
    virtual ~IAmAThing() {}
    virtual void TestThis() = 0;
};

class IAmTheOtherThing
{
public:
    virtual ~IAmTheOtherThing() {}
    virtual void TheOtherTest() = 0;
};

class TheThing : public IAmAThing
{
public:
    TheThing() {}
    void TestThis() {
        std::cout << "A Thing name" << std::endl;
    }
};

class TheOtherThing : public IAmTheOtherThing
{
    std::shared_ptr<IAmAThing> m_thing;
    string m_superInfo;

public:
    TheOtherThing(std::shared_ptr<IAmAThing> thing)
        : m_thing(thing) {
        m_superInfo = "From TheOtherThing";
    }
    TheOtherThing(std::shared_ptr<IAmAThing> thing, string sInfo)
        : m_thing(thing)
        , m_superInfo(sInfo) {
        m_superInfo = sInfo;
    }
    void TheOtherTest() {
        std::cout << m_superInfo << std::endl;
        m_thing->TestThis();
    }
};

class IHello
{
public:
    virtual void hello() const = 0;
    virtual ~IHello() = default;
};

class Hello : public IHello
{
public:
    virtual void hello() const {
        std::cout << "hello world!" << std::endl;
    }
};

class Privet : public IHello
{
public:
    virtual void hello() const {
        std::cout << "Privet world!" << std::endl;
    }
};



IOCContainer gConteiner;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //------Example #1----------------
    //Injector injector;
    IOCContainer conteiner;

    // Регистрируем IHello с классом Hello, т.о. каждый раз запрашивая IHell получаем объект Hello.
    // injector.registerInstance<IHello, Hello>();
    // auto helloInstance = injector.getObject<IHello>();
    // helloInstance->hello();
    // injector.registerInstance<IHello, Privet>();

    // //Здесь, после регистрации получим объект Privet
    // helloInstance = injector.getObject<IHello>();
    // helloInstance->hello();

    // //------Example #2----------------

    // gContainer.registerInstance<IAmAThing, TheThing>();
    // gContainer.registerFactory<IAmTheOtherThing, TheOtherThing, IAmAThing>();

    // gContainer.getObject<IAmAThing>()->TestThis();
    // gContainer.getObject<IAmTheOtherThing>()->TheOtherTest();

    // //Опять запршиваем объект,после последней регистрации получим объект Privet
    // helloInstance = injector.getObject<IHello>();
    // helloInstance->hello();

    // conteiner.registerFunctor<IProcessor>(std::function(
    //     []() -> std::shared_ptr<IProcessor>{
    //         return std::make_shared<IntelProcessor>("i7-12700K", ProcessorType::x86, 3.6);
    //     })
    //                                       );

    conteiner.registerInstance<IProcessor, IntelProcessor>();
    conteiner.registerFunctor<IProcessor>(std::function(
        []() -> std::shared_ptr<IProcessor>{
            return std::make_shared<IntelProcessor>("i7-12700K", ProcessorType::x86, 3.6);
        })
                                          );
    auto processorInstance = conteiner.getObject<IProcessor>();
    processorInstance->getProcessorInfo();


    conteiner.registerInstance<IProcessor, AMDProcessor>();
    conteiner.registerFunctor<IProcessor>(std::function(
        []() -> std::shared_ptr<IProcessor>{
            return std::make_shared<AMDProcessor>("A6-9500E OEM", ProcessorType::x64, 3.0);
        })
                                          );
    processorInstance = conteiner.getObject<IProcessor>();
    processorInstance->getProcessorInfo();

    std::cout<< "\n";
    conteiner.registerFactory<IComputer, Computer, IProcessor>();

    conteiner.getObject<IProcessor>()->getProcessorInfo();
    std::cout<< "\n";
    conteiner.getObject<IComputer>()->getComputer();





    return a.exec();
}
