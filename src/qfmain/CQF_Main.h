/********************************************************************
	filename: 	CQF_Main.h
	author:		Ling Song
	date: 		ÈýÔÂ 2017
*********************************************************************/
#ifndef CQF_Main_h__
#define CQF_Main_h__

#pragma once

#include "IQF_Main_Ext.h"
#include <map>
#include <vector>
#include "qf_config_internal.h"

QF_BEGIN_NAMESPACE(QF)

class IQF_Component;
class IQF_Activator;
class IQF_Command;
class IQF_Message;

typedef  std::map<std::string, IQF_Component*> QF_MainComponentMap;

typedef  std::map<std::string, IQF_Activator*> QF_MainActivatorMap;
typedef  std::map<std::string, void*> QF_MainInterfaceMap;

typedef std::map<std::string, IQF_Command*> QF_MainCommandMap;


typedef  std::map<const char*, int, ltstr> TQF_CharToIntMap;
typedef  std::map<int, int> TQF_IntToIntMap;

typedef std::vector<IQF_Message*> QF_MessageComponentList;
typedef std::map<std::string, QF_MessageComponentList*> QF_MainMessageListMap;

class CQF_Main:public IQF_Main_Ext
{
public:
    CQF_Main(const char* szEnterName ="", const char* szLibraryPath="", bool bInit=false);
    ~CQF_Main();

    bool Init(const char* szComponentFile = "components.cfg", const char* szPluginsFile = "plugins.cfg");

    //Subject Function
    void Attach(IQF_Observer* pObserver, const char* szMessage = "");
    void Detach(IQF_Observer* pObserver, const char* szMessage = "");
    void DetachAll();
    void Notify(const char* szMessage, int iValue = 0, void* pValue = 0);

    //Observer Function
    void Update(const char* szMessage, int iValue = 0, void* pValue = 0);

    //Main Function
    void Release();
    bool ExecuteCommand(const char* szCommandID, IQF_Properties* pInParam, IQF_Properties* pOutParam);
    void SendMessage(const char* szMessage, int iValue, void *pValue);
    void SendMessageQf(const char* szMessage, int iValue, void *pValue);
    void* GetInterfacePtr(const char* szInterfaceID);
    const char* GetConfigPath();
    //Ext
    void ResourceConstructed();
    IQF_Properties* CreateProperties();
    IQF_Property* CreateProperty();
    IQF_Subject* CreateSubject();
private:
    void RegisterLibrary(const char* szDllName);
    bool RegisterComponent(IQF_Component* pComponent);
    void RegisterActivator(IQF_Activator* pActivator);

    IQF_Subject* m_pSubject;
    QF_MainComponentMap m_components;
    QF_MainInterfaceMap m_interfaces;

    QF_MainActivatorMap m_activators;

	QF_MainCommandMap m_commands;

    QF_MainMessageListMap m_messagelists;

    TQF_CharToIntMap m_messageOrder;
    TQF_IntToIntMap m_messageInterfaceOrder;

    std::string m_configPath;
    std::string m_libraryPath;
    std::string m_enterName;
    bool m_inited;


};

QF_END_NAMESPACE

#endif // CQF_Main_h__
