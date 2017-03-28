#if ((defined(_MSC_VER) || defined(_WIN32_WCE)) && !defined(GISE_STATIC_LIBS)) || (defined(__HP_aCC) && defined(__HP_WINDLL))
#include <windows.h>
#include <winnt.h>
#include <string>
#include <stdio.h>
#include <assert.h>
#ifdef UNICODE
std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}
LPCWSTR S2LSTR(std::string s)
{ 
    std::wstring stemp = s2ws(s); 
    LPCWSTR result = stemp.c_str();
    return result;
} 

#else
#define S2LPWSTR(s) \
    ({  \
        (s.c_str()); \
    }) \  
#endif

#else
line.append(".so");
#endif  

#include "CQF_Main.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "IQF_Component.h"
#include "IQF_Activator.h"
#include <direct.h>


QF_BEGIN_NAMESPACE(QF)

typedef IQF_Component* (*componentFunc)(IQF_Main*);
typedef IQF_Activator* (*activatorFunc)(IQF_Main*);

CQF_Main::CQF_Main()
{
    m_pSubject = QF_CreateSubjectObject();
    {
        char buffer[MAX_PATH];
        getcwd(buffer, MAX_PATH);
        std::string componentsConfigFilePath = buffer;
        componentsConfigFilePath.append("/components.cfg");
        std::ifstream finComponents(componentsConfigFilePath.c_str(), std::ios::in);
        if (!finComponents)
        {
            std::cerr << "The components file can not be opened! Please check if it exists!" << std::endl;
            return;
        }
        std::string line;
        while (!finComponents.eof()) {
            std::getline(finComponents, line);
            RegisterLibrary(line.c_str());
        }
        finComponents.close();
    }

    {
        std::ifstream finPlugins("plugins.cfg", std::ios::in);
        if (!finPlugins)
        {
            std::cerr << "The plugins file can not be opened! Please check if it exists!" << std::endl;
            return;
        }
        std::string line;
        while (!finPlugins.eof()) {
            std::getline(finPlugins, line);
            RegisterLibrary(line.c_str());
        }
        finPlugins.close();
    }
    
}


CQF_Main::~CQF_Main()
{
}

void CQF_Main::RegisterLibrary(const char* szDllName)
{
    std::string line = szDllName;
    int foundExt = line.find_first_of(".");
    if (foundExt != std::string::npos)
    {
        line = line.substr(0, foundExt);
    }
#if ((defined(_MSC_VER) || defined(_WIN32_WCE)) && !defined(GISE_STATIC_LIBS)) || (defined(__HP_aCC) && defined(__HP_WINDLL))
    line.append(".dll");
    char buffer[MAX_PATH];
    getcwd(buffer, MAX_PATH);
    std::string dllPath = buffer;
    dllPath.append("\\");
    dllPath.append(line);
    HINSTANCE hdll = LoadLibrary(S2LSTR(dllPath));
    if (hdll != NULL)
    {
        componentFunc pf = (componentFunc)GetProcAddress(hdll, "QF_CreateComponentObject");
        if (pf)
        {
            RegisterComponent(pf(this));
            std::cout << "Load component " << dllPath << std::endl;
        }
        activatorFunc af = (activatorFunc)GetProcAddress(hdll, "QF_CreatePluginActivator");
        if (af)
        {
            RegisterActivator(af(this));
            std::cout << "Load component " << dllPath << std::endl;
        }
        
    }
    else
    {
        std::cout << "Load component failed: " << dllPath << std::endl;
    }
#else
    line.append(".so");
#endif  
}

void CQF_Main::RegisterComponent(IQF_Component* pComponent)
{
    if (!pComponent->Init())
    {
        assert(false && "Component Init Failed!");
        std::cout << "Component " << pComponent->GetComponentID() << " Init Failed!" << std::endl;
        return;
    }
    m_components[pComponent->GetComponentID()] = pComponent; 
    for (int i = 0; i < pComponent->GetInterfaceCount(); i++)
    {
        std::string id = pComponent->GetInterfaceID(i);

        if (id.empty())
        {
            assert(false && "Illegal Interface ID!");
            continue;
        }
        if (m_interfaces.find(id) != m_interfaces.end())
        {
            assert(false && "Interface Name has already exist! Please Rename!");
            std::cout << "Interface Name " << id << " has already exist! Please Rename!" << std::endl;
        }
        m_interfaces[id] = pComponent->GetInterfacePtr(id.c_str());
    }

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

bool CQF_Main::ExecuteCommand(int iCommandID, IQF_PropertySet* pInParam, IQF_PropertySet* pOutParam)
{
    return true;
}

void CQF_Main::SendMessage(const char* szMessage, int iValue, void *pValue)
{
    m_pSubject->Notify(szMessage, iValue, pValue);
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
        return NULL;
    }
    return it_interface->second;
}

void CQF_Main::RegisterResource(R* pR)
{
    for (QF_MainActivatorMap::iterator it = m_activators.begin();it!= m_activators.end();it++)
    {
        it->second->Register(pR);
    }
}

QF_END_NAMESPACE