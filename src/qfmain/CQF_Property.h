/********************************************************************
	FileName:    CQF_Property.h
	Author:        Ling Song
	Date:           Month 2 ; Year 2018
	Purpose:	     
*********************************************************************/
#ifndef CQF_Property_h__
#define CQF_Property_h__

#include "IQF_Property.h"
#include <string>

QF_BEGIN_NAMESPACE(QF)

class CQF_Property:public IQF_Property
{
public:
    CQF_Property();
    ~CQF_Property();

    virtual void Release();
    virtual const char* GetName();
    virtual bool SetName(const char* szName);
    virtual int GetType();
    virtual bool SetType(int iType);
    virtual const char* GetDesc();
    virtual bool SetDesc(const char* szDesc);
    virtual int GetInt();
    virtual bool SetInt(int iValue);
    virtual bool GetBool();
    virtual bool SetBool(bool bValue);
    virtual double GetDouble();
    virtual bool SetDouble(double dValue);
    virtual const char* GetString();
    virtual bool SetString(const char* szValue);
    virtual void* GetPtr();
    virtual void SetPtr(void* pPtr);

    virtual IQF_Property& operator=(const IQF_Property& right);

private:
    void Clear();
    int m_iType;
    void* m_pValue;
    void* m_pPtr;
    std::string m_szName;
    std::string m_szDesc;
};

QF_END_NAMESPACE
#endif // CQF_Property_h__