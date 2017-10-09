/********************************************************************
	FileName:    QObjectFactory.h
	Author:        Ling Song
	Date:           Month 6 ; Year 2017
	Purpose:	     
*********************************************************************/
#ifndef QObjectFactory_h__
#define QObjectFactory_h__

#pragma once

#include <memory>
#include <string>
#include <map>
#include <functional>
#include "Common/qtframework_com.h"


class QObject;


class QTFRAMEWORK_EXPORT QObjectRegister {
public:
    QObjectRegister(std::string className, std::function<QObject*(void)> classFactoryFunction);
};

#define REGISTER_QOBJECT(NAME, TYPE) static QObjectRegister TYPE##Register(NAME, [](void) -> QObject * { return new TYPE();});

class QTFRAMEWORK_EXPORT QObjectFactory
{
public:
    static QObjectFactory * Instance();

    void RegisterFactoryFunction(std::string name, std::function<QObject*(void)> classFactoryFunction);

    QObject* Create(std::string name);

private:
    QObjectFactory() {}
    std::map<std::string, std::function<QObject*(void)>> factoryFunctionRegistry;
};
#endif // QObjectFactory_h__



