#ifndef CFACTORY_H
#define CFACTORY_H

#include <functional>
#include <memory>
#include <iostream>
#include <map>
#include <string>
#include "factoryroot.h"


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

    std::shared_ptr<T> getObject() {
        return m_functor();
    }
};


#endif // CFACTORY_H
