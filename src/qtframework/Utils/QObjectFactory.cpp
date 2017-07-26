#include "QObjectFactory.h"


Registrar::Registrar(string name, function<QObject*(void)> classFactoryFunction)
{
    QObjectFactory::Instance()->RegisterFactoryFunction(name, classFactoryFunction);
}

QObjectFactory * QObjectFactory::Instance()
{
    static QObjectFactory factory;
    return &factory;
}


void QObjectFactory::RegisterFactoryFunction(string name, function<QObject*(void)> classFactoryFunction)
{
    // register the class factory function 
    factoryFunctionRegistry[name] = classFactoryFunction;
}

QObject* QObjectFactory::Create(string name)
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

