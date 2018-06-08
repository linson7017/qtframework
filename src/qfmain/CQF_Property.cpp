#include "CQF_Property.h"

#include "qf_config_internal.h"

QF_BEGIN_NAMESPACE(QF)


IQF_Property* QF_CreateProperty()
{
    return new CQF_Property();
}

CQF_Property::CQF_Property()
{
    m_szName = "";
    m_iType = QF_DataType_Undefined;
    m_pValue = 0;
}


CQF_Property::~CQF_Property()
{
    Clear();
}

void CQF_Property::Clear()
{
    switch (m_iType)
    {
    case QF_DataType_Integer:	delete (int*)m_pValue;	break;
    case QF_DataType_Bool:		delete (char*)m_pValue;	break;
    case QF_DataType_Double:	delete (double*)m_pValue;	break;
    case QF_DataType_String:	delete[](char*) m_pValue;	break;
    default:
        break;
    }

}

void CQF_Property::Release()
{
    delete this;
}

const char* CQF_Property::GetName()
{
    return m_szName.c_str();
}

bool CQF_Property::SetName(const char* szName)
{
    if (szName == NULL)
        return false;
    int len = strlen(szName);
    if (len == 0)
        return false;

    m_szName = szName;
    return true;
}
int CQF_Property::GetType()
{
    return m_iType;
}
bool CQF_Property::SetType(int iType)
{
    QF_ISVALID_DATATYPE(iType);
    if (!(QF_ISVALID_DATATYPE(iType)))
        return false;

    if (m_iType != QF_DataType_Undefined)
        return false;
    m_iType = iType;
    return true;
}
const char* CQF_Property::GetDesc()
{
    return m_szDesc.c_str();
}

bool CQF_Property::SetDesc(const char* szDesc)
{
    if (szDesc == NULL)
        return false;
    int len = strlen(szDesc);
    if (len == 0)
        return false;

    m_szDesc = szDesc;
    return true;
}

int CQF_Property::GetInt()
{
    int i_val = INT_MIN;
    if ((m_iType == QF_DataType_Integer) &&
        (m_pValue != NULL))
    {
        i_val = *((int*)m_pValue);
    }
    return i_val;
}

bool CQF_Property::SetInt(int iValue)
{
    if (m_iType != QF_DataType_Integer)
        return false;

    if (m_pValue == NULL)
        m_pValue = new int;

    *((int*)m_pValue) = iValue;

    return true;

}
bool CQF_Property::GetBool()
{
    bool b_val = false;
    if ((m_iType == QF_DataType_Bool) &&
        (m_pValue != NULL))
    {
        if (*((char*)m_pValue))
            b_val = true;
        else
            b_val = false;
    }
    return b_val;
}

bool CQF_Property::SetBool(bool bValue)
{
    if (m_iType != QF_DataType_Bool)
        return false;

    if (m_pValue == NULL)
        m_pValue = new char;

    *((char*)m_pValue) = bValue;
    return true;
}
double CQF_Property::GetDouble()
{
    double d_val = -DBL_MAX;

    if ((m_iType == QF_DataType_Double) &&
        (m_pValue != NULL))
    {
        d_val = *((double*)m_pValue);
    }
    return d_val;
}
bool CQF_Property::SetDouble(double dValue)
{
    if (m_iType != QF_DataType_Double)
        return false;

    if (m_pValue == NULL)
        m_pValue = new double;

    *((double*)m_pValue) = dValue;

    return true;

}
const char* CQF_Property::GetString()
{
    const char* sz_val = "";

    if ((m_iType == QF_DataType_String) &&
        (m_pValue != NULL))
    {
        sz_val = (const char*)m_pValue;
    }
    return sz_val;
}

bool CQF_Property::SetString(const char* szValue)
{

    if (m_iType != QF_DataType_String|| szValue==NULL)
    {
        return false;
    }
    else
    {
        if (m_pValue)
        {
            delete[]((char *)m_pValue);
        }
        m_pValue = new char[strlen(szValue) + 1];
        strcpy((char*)m_pValue, szValue);
    }
    return true;

}

void* CQF_Property::GetPtr()
{
    return m_pPtr;
}

void CQF_Property::SetPtr(void* pPtr)
{
    m_pPtr = pPtr;
}

IQF_Property& CQF_Property::operator=(const IQF_Property& right)
{
    Clear();
    IQF_Property* pright = (IQF_Property*)&right;

    this->SetName(pright->GetName());
    this->SetDesc(pright->GetDesc());
    this->SetType(pright->GetType());
    switch (this->GetType())
    {
    case QF_DataType_Integer: this->SetInt(pright->GetInt()); break;
    case QF_DataType_Bool: this->SetBool(pright->GetBool()); break;
    case QF_DataType_Double: this->SetDouble(pright->GetDouble()); break;
    case QF_DataType_String: this->SetString(pright->GetString()); break;
    default: assert(false);
    }
    return *this;
}


QF_END_NAMESPACE