#ifndef IQF_Main_h__
#define IQF_Main_h__

#pragma once
#include "IQF_Observer.h"
#include "IQF_Subject.h"

class R;
QF_BEGIN_NAMESPACE(QF)

class IQF_PropertySet;

class IQF_Main : public IQF_Observer, public IQF_Subject
{
public:
    virtual void Release() = 0;
    virtual bool ExecuteCommand(const char* szCommandID, IQF_PropertySet* pInParam, IQF_PropertySet* pOutParam) = 0;
    virtual void SendMessage(const char* szMessage, int iValue, void *pValue) = 0;
    virtual void SendMessageQf(const char* szMessage, int iValue, void *pValue) = 0;
    virtual void* GetInterfacePtr(const char* szInterfaceID) = 0;
    virtual void RegisterResource(R* pR)=0;
};

QF_API IQF_Main*  QF_CreateMainObject();

QF_END_NAMESPACE;

#endif // IQF_Main_h__
