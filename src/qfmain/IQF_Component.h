#ifndef IComponent_h__
#define IComponent_h__
#pragma once
#include "QF_Config.h"

QF_BEGIN_NAMESPACE(QF)

class IQF_Main;

class IQF_Component
{
public:
    virtual void Release() = 0;
    virtual bool Init() = 0;
    virtual void* GetInterfacePtr(const char* szInterfaceID) = 0;
    virtual const char* GetComponentID() = 0;
    virtual int GetInterfaceCount() = 0;
    virtual const char* GetInterfaceID(int iID) = 0;
};

#ifdef __cplusplus
extern "C" {
#endif

    QF_API IQF_Component* QF_CreateComponentObject(IQF_Main* pMain);


#ifdef __cplusplus
}
#endif

QF_END_NAMESPACE


#endif // IComponent_h__
