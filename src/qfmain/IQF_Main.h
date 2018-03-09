/********************************************************************
	filename: 	IQF_Main.h
	author:		Ling Song
	date: 		ÈýÔÂ 2017
*********************************************************************/
#ifndef IQF_Main_h__
#define IQF_Main_h__

#pragma once
#include "IQF_Observer.h"
#include "IQF_Subject.h"

class R;
QF_BEGIN_NAMESPACE(QF)

class IQF_Properties;

class IQF_Main : public IQF_Observer, public IQF_Subject
{
public:
    virtual void Release() = 0;
    virtual bool Init() = 0;
    virtual bool ExecuteCommand(const char* szCommandID, IQF_Properties* pInParam, IQF_Properties* pOutParam) = 0;
    virtual void SendMessage(const char* szMessage, int iValue, void *pValue) = 0;
    virtual void SendMessageQf(const char* szMessage, int iValue, void *pValue) = 0;
    virtual void* GetInterfacePtr(const char* szInterfaceID) = 0;
    virtual const char* GetConfigPath() = 0;
};

QF_API IQF_Main*  QF_CreateMainObject(const char* szEnterName="",const char* szLibraryPath="",bool bInit=true);

QF_END_NAMESPACE;

#endif // IQF_Main_h__
