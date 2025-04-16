#ifndef CFACTORY_H
#define CFACTORY_H
#include "factoryroot.h"
#include <functional>
#include <memory>
#include <iostream>
#include <map>
#include <string>

//Получить экземпляр объекта
template<typename T>
class CFactory : public FactoryRoot
{

    std::function<std::shared_ptr<T>()> m_functor;

public:
    ~CFactory() {}

    CFactory(std::function<std::shared_ptr<T>()> functor)
        : m_functor(functor)
    {
    }

    std::shared_ptr<T> GetObject() {
        return m_functor();
    }
};


#endif // CFACTORY_H
