/********************************************************************
	FileName:    IQF_Property.h
	Author:        Ling Song
	Date:           Month 2 ; Year 2018
	Purpose:	     
*********************************************************************/
#ifndef IQF_Property_h__
#define IQF_Property_h__
#include "QF_Config.h"

QF_BEGIN_NAMESPACE(QF)

class IQF_Property
{
public:
    virtual void Release() = 0;
    virtual const char* GetName() = 0;
    virtual bool SetName(const char* szName) = 0;
    virtual int GetType() = 0;
    virtual bool SetType(int iType) = 0;
    virtual const char* GetDesc() = 0;
    virtual bool SetDesc(const char* szDesc) = 0;
    virtual int GetInt() = 0;
    virtual bool SetInt(int iValue) = 0;
    virtual bool GetBool() = 0;
    virtual bool SetBool(bool bValue) = 0;
    virtual double GetDouble() = 0;
    virtual bool SetDouble(double dValue) = 0;
    virtual const char* GetString() = 0;
    virtual bool SetString(const char* szValue) = 0;

    virtual IQF_Property& operator=(const IQF_Property& right)=0;
};

#ifdef __cplusplus
extern "C" {
#endif
    QF_API IQF_Property* QF_CreateProperty();
#ifdef __cplusplus
}
#endif

class IQF_PropertyPtr
{
public:
    IQF_PropertyPtr()
    {
        m_ptr = QF_CreateProperty();
    }
    ~IQF_PropertyPtr()
    {
        if (m_ptr) m_ptr->Release();
    }
    IQF_Property* operator->() const
    {
        return m_ptr;
    }
    IQF_Property* Get()
    {
        return m_ptr;
    }
private:
    IQF_Property* m_ptr;

};

QF_END_NAMESPACE
#endif // IQF_Property_h__