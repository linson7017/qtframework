/********************************************************************
	FileName:    QObjectFactory.h
	Author:        Ling Song
	Date:           Month 6 ; Year 2017
	Purpose:	     
*********************************************************************/
#pragma once

#include <QObject>

#include <memory>
#include <string>
#include <map>
#include <functional>
#include "Common/qtframework_com.h"

using namespace  std;


class QTFRAMEWORK_EXPORT Registrar {
public:
    Registrar(string className, function<QObject*(void)> classFactoryFunction);
};

#define REGISTER_CLASS(NAME, TYPE) static Registrar TYPE##Registrar(NAME, [](void) -> QObject * { return new TYPE();});

class QTFRAMEWORK_EXPORT QObjectFactory
{
public:
    static QObjectFactory * Instance();

    void RegisterFactoryFunction(string name, function<QObject*(void)> classFactoryFunction);

    QObject* Create(string name);

private:
    QObjectFactory() {}
    map<string, function<QObject*(void)>> factoryFunctionRegistry;
};



