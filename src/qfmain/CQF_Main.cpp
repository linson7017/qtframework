#if ((defined(_MSC_VER) || defined(_WIN32_WCE)) && !defined(GISE_STATIC_LIBS)) || (defined(__HP_aCC) && defined(__HP_WINDLL))
//windows api
#include <windows.h>
#include <winnt.h>
#elif defined(QF_OS_LINUX)
// unix api
#include <dlfcn.h>
#endif  


#include "CQF_Main.h"

#include "IQF_Component.h"
#include "IQF_Activator.h"
#include "IQF_Command.h"
#include "IQF_Message.h"
#include "IQF_Properties.h"
#include "IQF_Property.h"
#include <direct.h>
#include "qf_eventdef.h"

#include "internal/qf_interfacedef.h"

//std
#include "QF_String.h"
#include <stdio.h>
#include <assert.h>
#include <sstream>
#include <fstream>
#include <iostream>

#include <mbilog.h>


QF_BEGIN_NAMESPACE(QF)

typedef IQF_Component* (*componentFunc)(IQF_Main*);
typedef IQF_Activator* (*activatorFunc)(IQF_Main*);


bool CheckValid(std::string& line)
{
    if (line.compare(0, 2, "//") == 0||
        line.compare(0, 1, "#") == 0||
        line.empty())
    {
        return false;
    }
    return true;
}

CQF_Main::CQF_Main(const char* szEnterName,const char* szLibraryPath, bool bInit):
    m_inited(false), 
    m_pSubject(QF_CreateSubjectObject()),
    m_enterName(szEnterName),
    m_libraryPath(szLibraryPath)
{ 
    if (strcmp(m_enterName.c_str(), "") == 0)
    {
        char buffer[MAX_PATH];
        getcwd(buffer, MAX_PATH);
        m_configPath = buffer;
    }
    else
    {
        std::string drive;
        std::string dir;
        std::string fname;
        std::string ext;
        splitpath(m_enterName.c_str(), drive, dir, fname, ext);
        m_configPath = dir.substr(0, dir.find_last_of("/") - 1);
        m_configPath = m_configPath.substr(0, m_configPath.find_last_of("/") + 1);
        m_configPath.append("qfconfig/" + fname);
        std::ifstream test(m_configPath + "/components.cfg", std::ios::in);
        if (!test)
        {
            m_configPath = dir + "qfconfig/" + fname;
        }
        test.close();
    }

    std::cout << "Config path is " << m_configPath << std::endl;

    if (strcmp(m_libraryPath.c_str(), "") == 0)
    {
        char buffer[MAX_PATH];
        getcwd(buffer, MAX_PATH);
        m_libraryPath = buffer;
    }
    std::cout << "Library path is " << m_libraryPath << std::endl;
    if (bInit)
    {
        Init();
    }
}


CQF_Main::~CQF_Main()
{
#ifndef _DEBUG
    try
    {
#endif

        this->SendMessage(QF_MESSAGE_MAIN_DELETE, 0, this);

        //delete message order
        for (TQF_CharToIntMap::iterator it_mainmessage_order = m_messageOrder.begin(); it_mainmessage_order != m_messageOrder.end(); it_mainmessage_order++)
        {
            char * p_str = (char *)it_mainmessage_order->first;
            delete[]p_str;
        }

        //delete message list
        for (QF_MainMessageListMap::iterator it_message = m_messagelists.begin(); it_message != m_messagelists.end(); it_message++)
        {
            QF_MessageComponentList * p_list = it_message->second;
            if (p_list)
                delete p_list;
        }

        // delete components
        for (QF_MainComponentMap::iterator it_component = m_components.begin(); it_component != m_components.end(); it_component++)
        {
            std::string str = it_component->first;
#ifndef _DEBUG
            try
            {
#endif
                it_component->second->Release();

#ifndef _DEBUG
            }
            catch (...)
            {
                char msg[2000];
                sprintf(msg, "Exception Occurs When Delete Component [%s] !", str.c_str());
            }
#endif
        }

        QF_ReleaseSubjectObject(m_pSubject);

#ifndef _DEBUG
    }
    catch (...)
    {
        
    }

#endif
}


bool CQF_Main::Init()
{
    m_inited = true;
    {
        std::string componentsFile = m_configPath + "/components.cfg";
        std::ifstream finComponents(componentsFile, std::ios::in);

        if (!finComponents)
        {
            std::cerr << "The components file can not be opened! Please check if it exists!" << std::endl;
            return false;
        }
        std::stringstream buffer;
        buffer << finComponents.rdbuf();
        finComponents.close();

        std::string inputStr(buffer.str());
        std::string cleanStr;
        remove_comment(inputStr, cleanStr);
        std::stringstream ss;
        ss.str(cleanStr);
        std::string line;
        while (!ss.eof()) {
            std::getline(ss, line);
            if (CheckValid(line))
            {
                RegisterLibrary(line.c_str());
            }
        }
    }

    {
        std::string pluginsFile = m_configPath + "/plugins.cfg";
        std::ifstream finPlugins(pluginsFile, std::ios::in);
        if (!finPlugins)
        {
            std::cerr << "The plugins file can not be opened! Please check if it exists!" << std::endl;
            return false;
        }
        std::stringstream buffer;
        buffer << finPlugins.rdbuf();
        finPlugins.close();

        std::string inputStr(buffer.str());
        std::string cleanStr;
        remove_comment(inputStr, cleanStr);
        std::stringstream ss;
        ss.str(cleanStr);
        std::string line;
        while (!ss.eof()) {
            std::getline(ss, line);
            if (CheckValid(line))
            {
                RegisterLibrary(line.c_str());
            }
        }
    }
    return true;
}

const char* CQF_Main::GetConfigPath()
{
    return m_configPath.c_str();
}

void CQF_Main::RegisterLibrary(const char* szDllName)
{
    std::string line = szDllName;
    int foundExt = line.find_first_of(".");
    if (foundExt != std::string::npos)
    {
        line = line.substr(0, foundExt);
    }
#ifdef QF_OS_WIN
    line.append(".dll");
    /*char buffer[MAX_PATH];
    getcwd(buffer, MAX_PATH);*/
    std::string dllPath = m_libraryPath;
    dllPath.append("/");
    dllPath.append(line);
    
    //should selected unicode
    HINSTANCE pHnd = LoadLibraryW((wchar_t*)s2ws(dllPath).c_str());
    
    char buf[100];
    if (pHnd != NULL)
    {
        componentFunc pf = (componentFunc)GetProcAddress(pHnd, "QF_CreateComponentObject");
        activatorFunc af = (activatorFunc)GetProcAddress(pHnd, "QF_CreatePluginActivator");
        if (pf)
        {
            RegisterComponent(pf(this));
            sprintf(buf, "Load component %s.\n", dllPath.c_str());
            SendMessageQf("QFMAIN_LOAD_COMPONENT_MESSAGE", 0, buf);
            printf(buf);
        }     
        else if (af)
        {
            RegisterActivator(af(this));
            sprintf(buf, "Load plugin %s.\n", dllPath.c_str());
            SendMessageQf("QFMAIN_LOAD_COMPONENT_MESSAGE", 0, buf);
            printf(buf);
        }
        else
        {
            sprintf(buf, "Unable to find plugin interface %s.\n", dllPath.c_str());
            SendMessageQf("QFMAIN_LOAD_COMPONENT_MESSAGE", 0, buf);
            printf(buf);
            FreeLibrary(pHnd);
        }
    }
    else
    {
        TCHAR szBuf[80];
        LPVOID lpMsgBuf;
        DWORD dw = GetLastError();

        sprintf(buf, "Load component failed: %s. Error Code: %lu", dllPath.c_str(),dw);
        SendMessageQf("QFMAIN_LOAD_COMPONENT_MESSAGE", 0, buf);
        printf(buf);

    }
#elif defined(QF_OS_LINUX)
    line.append(".so");
    /*char buffer[MAX_PATH];
    getcwd(buffer, MAX_PATH);*/
    std::string dllPath = m_libraryPath;
    dllPath.append("/");
    dllPath.append(line);
    void* pHnd = dlopen(dllPath.c_str());
    f(pHnd != NULL)
    {
        componentFunc pf = (componentFunc)dlsym(pHnd, "QF_CreateComponentObject");
        if (pf)
        {
            RegisterComponent(pf(this));
            std::cout << "Load component " << dllPath << std::endl;
        }
        else
        {
            std::cout << "Load component " << dllPath<<" failed! Can not find component interface. Error code:"<<dlerror() << std::endl;
            dlclose(pHnd);
        }
        activatorFunc af = (activatorFunc)dlsym(pHnd, "QF_CreatePluginActivator");
        if (af)
        {
            RegisterActivator(af(this));
            std::cout << "Load plugin " << dllPath << std::endl;
        }
        else
        {
            std::cout << "Load component " << dllPath << " failed! Can not find plugin interface. Error code:" << dlerror() << std::endl;
            dlclose(pHnd);
        }
    }
    else
    {
        std::cout << "Load component " << dllPath << "failed! Error code:"<< dlerror()<< std::endl;


    }
#endif  
}

bool CQF_Main::RegisterComponent(IQF_Component* pComponent)
{
#ifndef _DEBUG
    try
    {
#endif
        if (!pComponent)
        {
            char sz_msg[1024];
            sprintf(sz_msg, "pComponent == NULL");
            assert(false && "Illegal Component ! ");
            return false;
        }
        const char* component_id = pComponent->GetComponentID();
        if (!component_id)
        {
            char sz_msg[1024];
            sprintf(sz_msg, "component_id == NULL");
            assert(false && "Illegal Component ID !");
            return false;
        }

        if (!pComponent->Init())
        {
            assert(false && "Component Init Failed!");
            std::cout << "Component " << pComponent->GetComponentID() << " Init Failed!" << std::endl;
            return false;
        }

        char* p_str = new char[strlen(component_id) + 1];
        strcpy(p_str, component_id);
        m_components[p_str] = pComponent;

        //register interfaces
        for (int i = 0; i < pComponent->GetInterfaceCount(); i++)
        {
            std::string interface_id = pComponent->GetInterfaceID(i);

            if (interface_id.empty())
            {
                assert(false && "Illegal Interface ID!");
                continue;
            }

            if (interface_id.compare(QF_INTERFACE_MAIN_COMMAND)!=0 && 
                interface_id.compare(QF_INTERFACE_MAIN_MESSAGE) != 0)
            {
                if (m_interfaces.find(interface_id) != m_interfaces.end())
                {
                    assert(false && "Interface Name has already exist! Please Rename!");
                    std::cout << "Interface Name " << interface_id << " has already exist! Please Rename!" << std::endl;
                }
                m_interfaces[interface_id] = pComponent->GetInterfacePtr(interface_id.c_str());
            }        
        }

        // Register Commands
        IQF_Command * p_interface_command = (IQF_Command *)pComponent->GetInterfacePtr(QF_INTERFACE_MAIN_COMMAND);
        if (p_interface_command != NULL)
        {
            for (int i = 0; i < p_interface_command->GetCommandCount(); i++)
            {
                std::string command_id = p_interface_command->GetCommandID(i);

                if (command_id.empty())
                {
                    assert(false && "Illegal Command ID");
                    continue;
                }

                if (m_commands.find(command_id) != m_commands.end())
                {
                    assert(false && "Command ID Repeat");
                    printf("Command ID[%s] Repeat，Please Choose Another ID.\n", command_id);
                }
                m_commands[command_id] = p_interface_command;
            }
        }

        // Register message component
        IQF_Message * p_interface_message = (IQF_Message*)pComponent->GetInterfacePtr(QF_INTERFACE_MAIN_MESSAGE);
        if (p_interface_message != NULL)
        {
            QF_MainMessageListMap::iterator it;
            int i_count = p_interface_message->GetMessageCount();
            for (int i = 0; i < i_count; i++)
            {
                // record id
                const std::string sz_message_id = p_interface_message->GetMessageID(i);
                if (sz_message_id.empty())
                {
                    assert(false && "Illegal Message ID");
                    continue;
                }

                // scan if already has the message
                it = m_messagelists.find(sz_message_id);

                QF_MessageComponentList * p_list = NULL;
                // if message exist
                if (it != m_messagelists.end())
                {
                    p_list = it->second;
                }
                // if not, new one
                else
                {
                    p_list = new QF_MessageComponentList;
                    m_messagelists[sz_message_id] = p_list;
                }

                TQF_CharToIntMap::iterator it_order = m_messageOrder.find(component_id);

                // 找到
                if (it_order != m_messageOrder.end())
                {
                    int i_index = it_order->second;

                    int i_order;
                    for (i_order = 0; i_order < p_list->size(); i_order++)
                    {
                        IQF_Message * p_message = (*p_list)[i_order];
                        TQF_IntToIntMap::iterator it_message_order = m_messageInterfaceOrder.find((int)p_message);
                        if (it_message_order == m_messageInterfaceOrder.end())
                        {
                            char sz_msg[1024];
                            sprintf(sz_msg, "Message send order error !");
                            std::cout << "CGIS_Main::RegisterComponent "<<sz_msg << std::endl;
                            assert(false);
                            m_messageInterfaceOrder[(int)p_interface_message] = -1;
                            p_list->push_back(p_interface_message);
                            break;
                        }
                        else
                        {
                            int i_message_order = it_message_order->second;
                            if ((i_message_order == -1) || (i_message_order > i_index))
                            {
                                p_list->insert(p_list->begin() + i_order, p_interface_message);
                                break;
                            }
                        }
                    }
                    // 没有插入
                    if (i_order >= p_list->size())
                    {
                        p_list->push_back(p_interface_message);
                    }
                    m_messageInterfaceOrder[(int)p_interface_message] = i_index;
                }
                // 没找到
                else
                {
                    m_messageInterfaceOrder[(int)p_interface_message] = -1;
                    p_list->push_back(p_interface_message);
                }
            }
        }
#ifndef _DEBUG
    }
    catch (...)
    {
        char sz_msg[1024] = "";
        sprintf(sz_msg, "Register Component %s error !", pComponent->GetComponentID());
    }
#endif
    return true;
}

void CQF_Main::RegisterActivator(IQF_Activator* pActivator)
{
    if (!pActivator->Init())
    {
        assert(false && "Component Init Failed!");
        std::cout << "Component " << pActivator->GetID() << " Init Failed!" << std::endl;
        return;
    }
    m_activators[pActivator->GetID()] = pActivator;
    pActivator->Register();
}

void CQF_Main::Attach(IQF_Observer* pObserver, const char* szMessage)
{
    m_pSubject->Attach(pObserver);
}

void CQF_Main::Detach(IQF_Observer* pObserver, const char* szMessage)
{
    m_pSubject->Detach(pObserver);
}

void CQF_Main::DetachAll()
{
    m_pSubject->DetachAll();
}

void CQF_Main::Notify(const char* szMessage, int iValue, void* pValue)
{
    SendMessage(szMessage, iValue, pValue);
}

//Observer Function
void CQF_Main::Update(const char* szMessage, int iValue, void* pValue)
{
    SendMessage(szMessage, iValue, pValue);
}

//Main Function
void CQF_Main::Release()
{
    delete this;
}

bool CQF_Main::ExecuteCommand(const char* szCommandID, IQF_Properties* pInParam, IQF_Properties* pOutParam)
{
    QF_MainCommandMap::iterator it_command;


    it_command = m_commands.find(szCommandID);
    if (it_command == m_commands.end())
    {
        assert(false && "Can not find the component for command");
        return false;
    }

    IQF_Command * p_command = it_command->second;

#ifndef _DEBUG
    try
    {                                                                                                                                             
#endif
        return p_command->ExecuteCommand(szCommandID, pInParam, pOutParam);
#ifndef _DEBUG
    }
    catch (...)
    {
        char msg[2000];
        sprintf(msg, "An Exception Occurs  When Execute Command [%d] .", szCommandID);
        return false;
    }
#endif
}

void CQF_Main::SendMessage(const char* szMessage, int iValue, void *pValue)
{
#ifndef _DEBUG
    try
    {
#endif
        m_pSubject->Notify(szMessage, iValue, pValue);

        QF_MainMessageListMap::iterator it = m_messagelists.find(szMessage);
        // message does not exist
        if (it == m_messagelists.end())
            return;

        // scan message list
        QF_MessageComponentList * p_list = it->second;
        int i;
        for (i = 0; i < p_list->size(); i++)
        {
            IQF_Message * p_message = (*p_list)[i];
            if (p_message)
            {
                p_message->OnMessage(szMessage, iValue, pValue);
            }
            else
            {
                assert(false && "Illegal message interface! ");
            }
        }
#ifndef _DEBUG
    }
    catch (...)
    {
        assert(false && "Exception" && "Illegal message interface! ");
    }
#endif
}

void CQF_Main::SendMessageQf(const char* szMessage, int iValue, void *pValue)
{
    SendMessage(szMessage, iValue, pValue);
}

void* CQF_Main::GetInterfacePtr(const char* szInterfaceID)
{
    QF_MainInterfaceMap::iterator it_interface = m_interfaces.find(szInterfaceID);
    if (it_interface == m_interfaces.end())
    {
#ifndef _DEBUG
        std::cout << "Get interface "<< szInterfaceID <<" failed ! Please check if the interface exists or the related component is registered ! "<< std::endl;
#endif
        return NULL;
    }
    return it_interface->second;
}


void CQF_Main::ResourceConstructed()
{
    for (QF_MainActivatorMap::iterator it = m_activators.begin(); it != m_activators.end(); it++)
    {
        it->second->Constructed();
    }
}

IQF_Properties* CQF_Main::CreateProperties()
{
    return QF_CreateProperties();
}

IQF_Property* CQF_Main::CreateProperty()
{
    return QF_CreateProperty();
}

IQF_Subject* CQF_Main::CreateSubject()
{
    return QF_CreateSubjectObject();
}

QF_END_NAMESPACE