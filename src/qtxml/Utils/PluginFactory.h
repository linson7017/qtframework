/********************************************************************
	FileName:    PluginFactory.h
	Author:        Ling Song
	Date:           Month 9 ; Year 2017
	Purpose:	     
*********************************************************************/
#ifndef PluginFactory_h__
#define PluginFactory_h__


#include <memory>
#include <string>
#include <map>
#include <functional>
#include "Common/qtxml_com.h"

namespace QF
{
    class QF_Plugin;
}

namespace QF
{
    class QTXML_EXPORT PluginRegister {
    public:
        PluginRegister(std::string className, std::function<QF::QF_Plugin*(void)> classFactoryFunction);
    };

    class QTXML_EXPORT PluginFactory
    {
    public:
        static PluginFactory * Instance();

        void RegisterFactoryFunction(std::string name, std::function<QF::QF_Plugin*(void)> classFactoryFunction);

        QF::QF_Plugin* Create(std::string name);

    private:
        PluginFactory() {}
        std::map<std::string, std::function<QF::QF_Plugin*(void)>> factoryFunctionRegistry;
    };
}


#define REGISTER_PLUGIN(NAME, TYPE) static QF::PluginRegister TYPE##PluginRegister(NAME, [](void) -> QF::QF_Plugin * { return new TYPE();});


#endif // PluginFactory_h__