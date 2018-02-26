#include "QObjectFactory.h"


QObjectRegister::QObjectRegister(std::string name, std::function<QObject*(void)> classFactoryFunction)
{
    QObjectFactory::Instance()->RegisterFactoryFunction(name, classFactoryFunction);
}

QObjectFactory * QObjectFactory::Instance()
{
    static QObjectFactory factory;
    return &factory;
}


void QObjectFactory::RegisterFactoryFunction(std::string name, std::function<QObject*(void)> classFactoryFunction)
{
    // register the class factory function 
    factoryFunctionRegistry[name] = classFactoryFunction;
}

QObject* QObjectFactory::Create(std::string name)
{
    QObject * instance = nullptr;

    auto it = factoryFunctionRegistry.find(name);
    if(it != factoryFunctionRegistry.end())
        instance = it->second();
    
    // wrap instance in a shared ptr and return
    if(instance != nullptr)
        return instance;
    else
        return nullptr;
}

