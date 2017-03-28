#ifndef CQF_Main_h__
#define CQF_Main_h__

#pragma once

#include "IQF_Main.h"
#include <map>

QF_BEGIN_NAMESPACE(QF)

class IQF_Component;
class IQF_Activator;

typedef  std::map<std::string, IQF_Component*> QF_MainComponentMap;

typedef  std::map<std::string, IQF_Activator*> QF_MainActivatorMap;
typedef  std::map<std::string, void*> QF_MainInterfaceMap;

class CQF_Main:public IQF_Main
{
public:
    CQF_Main();
    ~CQF_Main();

    //Subject Function
    void Attach(IQF_Observer* pObserver, const char* szMessage = "");
    void Detach(IQF_Observer* pObserver, const char* szMessage = "");
    void DetachAll();
    void Notify(const char* szMessage, int iValue = 0, void* pValue = 0);

    //Observer Function
    void Update(const char* szMessage, int iValue = 0, void* pValue = 0);

    //Main Function
    void Release();
    bool ExecuteCommand(int iCommandID, IQF_PropertySet* pInParam, IQF_PropertySet* pOutParam);
    void SendMessage(const char* szMessage, int iValue, void *pValue);
    void SendMessageQf(const char* szMessage, int iValue, void *pValue);
    void* GetInterfacePtr(const char* szInterfaceID);
    void RegisterResource(R* pR);
private:
    void RegisterLibrary(const char* szDllName);
    void RegisterComponent(IQF_Component* pComponent);
    void RegisterActivator(IQF_Activator* pActivator);

    IQF_Subject* m_pSubject;
    QF_MainComponentMap m_components;
    QF_MainInterfaceMap m_interfaces;

    QF_MainActivatorMap m_activators;
};

QF_END_NAMESPACE

#endif // CQF_Main_h__
