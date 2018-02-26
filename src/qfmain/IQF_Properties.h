/********************************************************************
	FileName:    IQF_Properties.h
	Author:        Ling Song
	Date:           Month 2 ; Year 2018
	Purpose:	     
*********************************************************************/
#ifndef IQF_Properties_h__
#define IQF_Properties_h__
#include "QF_Config.h"

QF_BEGIN_NAMESPACE(QF)

class IQF_Property;
class IQF_Properties
{
public:
    virtual void Release() = 0;
    virtual void Clear() = 0;
    virtual int GetCount() = 0;
    virtual IQF_Property* GetProperty(const char* szName) = 0;
    virtual bool HasProperty(const char* szName) = 0;
    virtual bool AddProperty(const char* szName, IQF_Property* pProperty) = 0;
    virtual IQF_Property* AddProperty(const char* szName, int iType) = 0;
    virtual  IQF_Property* GetFirstProperty() = 0;
    virtual  IQF_Property* GetNextProperty(IQF_Property* pCurrentProperty) = 0;
    virtual bool DeleteProperty(const char* szName) = 0;
    virtual  bool SetIntProperty(const char* szName, int iValue) = 0;
    virtual bool SetBoolProperty(const char* szName, bool bValue) = 0;
    virtual  bool SetDoubleProperty(const char* szName, bool dValue) = 0;
    virtual  bool SetStringProperty(const char* szName, const char* szValue) = 0;
};


#ifdef __cplusplus
extern "C" {
#endif
    QF_API IQF_Properties* QF_CreateProperties();
#ifdef __cplusplus
}
#endif

class IQF_PropertiesPtr
{
public:
    IQF_PropertiesPtr()
    {
        m_ptr = QF_CreateProperties();
    }
    ~IQF_PropertiesPtr()
    {
        if (m_ptr) m_ptr->Release();
    }
    IQF_Properties* operator->() const
    {
        return m_ptr;
    }
    IQF_Properties* Get()
    {
        return m_ptr;
    }
private:
    IQF_Properties * m_ptr;

};


QF_END_NAMESPACE

#endif // IQF_Properties_h__