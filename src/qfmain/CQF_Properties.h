/********************************************************************
	FileName:    CQF_Properties.h
	Author:        Ling Song
	Date:           Month 2 ; Year 2018
	Purpose:	     
*********************************************************************/
#ifndef CQF_Properties_h__
#define CQF_Properties_h__

#pragma once
#include "IQF_Properties.h"
#include <map>
#include <string>

QF_BEGIN_NAMESPACE(QF)

class IQF_Property;
class CQF_Properties  :public IQF_Properties
{
public:
    CQF_Properties();
    ~CQF_Properties();
    void Release();
    void Clear();
    int GetCount();
    IQF_Property* GetProperty(const char* szName);
    bool HasProperty(const char* szName);
    bool AddProperty(const char* szName, IQF_Property* pProperty);
    IQF_Property* AddProperty(const char* szName, int iType);
    IQF_Property* GetFirstProperty();
    IQF_Property* GetNextProperty(IQF_Property* pCurrentProperty);
    bool DeleteProperty(const char* szName);
    bool SetIntProperty(const char* szName, int iValue);
    bool SetBoolProperty(const char* szName, bool bValue);
    bool SetDoubleProperty(const char* szName, bool dValue);
    bool SetStringProperty(const char* szName, const char* szValue);
    int GetIntProperty(const char* szName, int iValue) ;
    bool GetBoolProperty(const char* szName, bool bValue) ;
    double GetDoubleProperty(const char* szName, bool dValue) ;
    const char* GetStringProperty(const char* szName, const char* szValue) ;
private:
    typedef std::map<std::string, IQF_Property*> ProperteisMapType;
    ProperteisMapType m_properties;
    ProperteisMapType::iterator m_propertiesIterator;
};

QF_END_NAMESPACE
#endif // CQF_Properties_h__