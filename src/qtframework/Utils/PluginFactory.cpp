#include "PluginFactory.h"

using namespace QF;

PluginRegister::PluginRegister(std::string name, std::function<QF::QF_Plugin*(void)> classFactoryFunction)
{
    PluginFactory::Instance()->RegisterFactoryFunction(name, classFactoryFunction);
}

PluginFactory * PluginFactory::Instance()
{
    static PluginFactory factory;
    return &factory;
}


void PluginFactory::RegisterFactoryFunction(std::string name, std::function<QF::QF_Plugin*(void)> classFactoryFunction)
{
    // register the class factory function 
    factoryFunctionRegistry[name] = classFactoryFunction;
}

QF::QF_Plugin* PluginFactory::Create(std::string name)
{
    QF::QF_Plugin * instance = nullptr;

    auto it = factoryFunctionRegistry.find(name);
    if (it != factoryFunctionRegistry.end())
        instance = it->second();

    // wrap instance in a shared ptr and return
    if (instance != nullptr)
        return instance;
    else
        return nullptr;
}


