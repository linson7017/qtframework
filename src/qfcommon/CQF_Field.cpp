#include <qf_config_internal.h>
#include <qfcommon/IQF_databuffer.h>
#include <qfcommon/IQF_propertyset.h>

#include "CQF_Field.h"

QF_BEGIN_NAMESPACE(QF)


//##ModelId=3F90FD54013B
CQF_Field::CQF_Field()
{
	Init() ;
}

//##ModelId=3F90FD590199
CQF_Field::~CQF_Field()
{
	Clear() ;
}

//##ModelId=3F90F92C01EA
const char* CQF_Field::GetName()
{
	return m_szName ;
}

//##ModelId=3F90F92C01EB
int CQF_Field::GetType()
{
	return m_iType; 
}

//##ModelId=3F90F92C01EC
const char* CQF_Field::GetStereoType()
{
	return m_szStereoType ;
}

//##ModelId=3F90F92C01ED
unsigned int CQF_Field::GetLength()
{
	switch(m_iType)
	{
	case QF_INTEGER:
		return sizeof(int) ;
	case QF_BOOL:
		return sizeof(char) ;
	case QF_DOUBLE :
		return sizeof(double) ;
	case QF_STRING :
		if (!m_pValue)
			return 0 ;
		else
			return strlen((char *)m_pValue) + 1 ;
	case QF_BINARY :
		return sizeof(int) ;
	default:
		assert(false) ;
		return 0 ;
	}
}

//##ModelId=3F90F92C01F8
bool CQF_Field::IsNullable()
{
	return (m_iFlags & 0x1) ;
}

//##ModelId=3F90F92C01FB
const char* CQF_Field::GetCaption()
{
	return m_szCaption ;
}

//##ModelId=3F90F92C01FC
const char* CQF_Field::GetDesc()
{
	return m_szDesc ;
}

//##ModelId=3F90F92C01FE
bool CQF_Field::SetName(const char* szName)
{
	// 判断参数的合法性：
	//		不能为空；
	//		长度不能为0

	if (szName == NULL)
		return false ;

	int len = strlen(szName) ;
	if (len == 0)
		return false ;

	// 字段名不能修改，如果已经设置过，则不能再设置
	if (strlen(m_szName) > 0)
		return false ;

	// 分配内存，并拷贝字符串
	m_szName = new char [len + 1] ;
	strcpy(m_szName, szName) ;

	// 将字段名改为大写
	_strupr (m_szName) ;

	return true ;
}

//##ModelId=3F90F92C0208
bool CQF_Field::SetType(int type)
{
	// 检验数据类型合法性
	assert (QF_ISVALID_DATATYPE(type)) ;

	if (!(QF_ISVALID_DATATYPE(type)))
		return false ;

	// 如果已经设置过类型，则不能再重新设置
	assert (m_iType == QF_UNDEFINED) ;

	if (m_iType != QF_UNDEFINED)
		return false ;

	m_iType = type ;
	m_iExtType = m_iType ;

	// 根据数据类型,设置缺省长度
	switch(type)
	{
		case QF_INTEGER	: /*m_uiLength = sizeof (int) ; */break ;
		case QF_BOOL		: /*m_uiLength = sizeof (char) ; */break ;
		case QF_DOUBLE		: /*m_uiLength = sizeof (double) ; */break ;
		case QF_STRING		: break ;
		case QF_BINARY		: 
			{
				m_pValue = (void* )QF_CreateDataBufferObject(0) ;
				m_iFlags &= ~0x2 ;
				break ;
			}
		default : 
			{
				assert(false) ;
				return false ;
			}
	}

	return true ;
}

//##ModelId=3F90F92C020A
bool CQF_Field::SetStereoType(const char* szStereoType)
{
	// 首先清除内存
	// 如果参数为空，则将成员变量也设为空字符串
	if (strlen(m_szStereoType) > 0)
	{
		delete[] m_szStereoType ;
		m_szStereoType = "" ;
	}

	if (szStereoType)
	{
		int len = strlen(szStereoType) ;
		if (len > 0)
		{
			// 分配内存，并拷贝字符串
			m_szStereoType = new char [len + 1] ;
			strcpy(m_szStereoType, szStereoType) ;
		}
	}

	return true ;
}

//##ModelId=3F90F92C020E
bool CQF_Field::SetNullable(bool bNullable)
{
	if (bNullable)
		m_iFlags |= 0x1 ;
	else
		m_iFlags &= ~0x1 ;

	return true ;
}

//##ModelId=3F90F92C021A
bool CQF_Field::SetCaption(const char* szCaption)
{
	// 首先清除内存
	// 如果参数为空，则将成员变量也设为空字符串
	if (strlen(m_szCaption) > 0)
	{
		delete[] m_szCaption ;
		m_szCaption = "" ;
	}

	if (szCaption)
	{
		int len = strlen(szCaption) ;
		if (len > 0)
		{
			// 分配内存，并拷贝字符串
			m_szCaption = new char [len + 1] ;
			strcpy(m_szCaption, szCaption) ;
		}
	}

	return true ;
}

//##ModelId=3F90F92C021C
bool CQF_Field::SetDesc(const char* szDesc)
{
	// 首先清除内存
	// 如果参数为空，则将成员变量也设为空字符串
	if (strlen(m_szDesc) > 0)
	{
		delete[] m_szDesc ;
		m_szDesc = "" ;
	}

	if (szDesc)
	{
		int len = strlen(szDesc) ;
		if (len > 0)
		{
			// 分配内存，并拷贝字符串
			m_szDesc = new char [len + 1] ;
			strcpy(m_szDesc, szDesc) ;
		}
	}

	return true ;
}



//##ModelId=3F90F92C0228
int CQF_Field::GetInt()
{
	assert (m_iType == QF_INTEGER) ;
	assert (!(m_iFlags & 0x2)) ;
	assert (m_pValue) ;

	int i_val = INT_MIN ; 
	
	// 如果类型不对，或还未被设置，则返回0 。
	// 如果为空，则返回INT_MIN

	if ((m_iType == QF_INTEGER) &&
		!(m_iFlags & 0x2) &&
		(m_pValue != NULL))
	{
		i_val = * ((int*) m_pValue ) ;
	}

	return i_val ;
}

//##ModelId=3F90F92C0229
double CQF_Field::GetDouble()
{
	assert (m_iType == QF_DOUBLE) ;
	assert (!(m_iFlags & 0x2)) ;
	assert (m_pValue) ;

	double d_val = -DBL_MAX ;

	// 如果类型不对，或还未被设置，则返回0 。

	if ((m_iType == QF_DOUBLE) &&
		!(m_iFlags & 0x2) &&
		(m_pValue != NULL))
	{
		d_val = * ((double*) m_pValue ) ;
	}

	return d_val ;
}

//##ModelId=3F90F92C022A
const char* CQF_Field::GetString()
{
	assert (m_iType == QF_STRING ) ;
	assert (!(m_iFlags & 0x2)) ;
	assert (m_pValue) ;

	const char* sz_val = "" ;

	// 如果类型不对，或还未被设置，则返回空字符串（不是空指针） 。

	if ((m_iType == QF_STRING ) &&
		!(m_iFlags & 0x2) &&
		(m_pValue != NULL))
	{
		sz_val = (const char*) m_pValue ;
	}

	return sz_val ;
}


//##ModelId=3F90F92C022B
bool CQF_Field::GetValueAsString(char* szValueString,int iLength)
{
	if (!szValueString || iLength < 2)
	{
		assert(false) ;
		return false;
	}

	if ((m_iFlags & 0x2) || !m_pValue)
	{
		strcpy(szValueString, "");
		return false;
	}

	char sz_value[50] ;
	switch (m_iType)
	{
		case QF_INTEGER :
		{
			sprintf(sz_value, "%d", GetInt()) ;
			strncpy(szValueString, sz_value, iLength - 1) ;
			szValueString[iLength - 1] = '\0' ;
			break ;
		}
		case QF_BOOL :
		{
			if (GetBool())
				strncpy(szValueString, "TRUE", iLength - 1) ;
			else
				strncpy(szValueString, "FALSE", iLength - 1) ;
			szValueString[iLength - 1] = '\0' ;
			break ;
		}
		case QF_DOUBLE :
		{
			sprintf(sz_value, "%f", GetDouble()) ;
			strncpy(szValueString, sz_value, iLength - 1) ;
			szValueString[iLength - 1] = '\0' ;
			break ;
		}
		case QF_STRING : 
		{
			strncpy(szValueString, GetString(), iLength - 1) ;
			szValueString[iLength - 1] = '\0' ;
			break ;
		}
		case QF_BINARY :
		{
/*			IQF_DataBuffer* pdatabuffer = (IQF_DataBuffer*) m_pValue ;
			int size = pdatabuffer->GetSize () ;

			// 首先申请足够长度的buffer
			char* pbuffer = new char [size * 2] ;

			// 进行Base64编码
			QF_EncodeBase64((const unsigned char *)(pdatabuffer->GetBufferPtr()),pbuffer, size, 80) ;

			// 如果长度超过给定长度，则返回错误
			assert(strlen(pbuffer) < (unsigned) iLength) ;
			if (strlen(pbuffer) >= (unsigned)iLength)
			{
				delete[] pbuffer ;
				return false ;
			}

			strcpy(szValueString, pbuffer) ;

			delete[] pbuffer ;
*/assert(false);
			break ;
		}
		default:
		{
			strcpy(szValueString, "");
			return false;
		}
	}

	return true ;
}

//##ModelId=3F90F92C022D
bool CQF_Field::SetInt(int iValue)
{
	assert (m_iType == QF_INTEGER) ;

	if (m_iType != QF_INTEGER) 
		return false;

	// 如果还未申请内存，则申请
	if (m_pValue == NULL)
		m_pValue = new int ;

	* ( (int*) m_pValue ) = iValue ;

	SetToNull(false) ;

	return true ;
}

//##ModelId=3F90F92C0237
bool CQF_Field::SetDouble(double dValue)
{
	assert (m_iType == QF_DOUBLE) ;

	if (m_iType != QF_DOUBLE) 
		return false;

	// 如果还未申请内存，则申请
	if (m_pValue == NULL)
		m_pValue = new double ;

	* ( (double*) m_pValue ) = dValue ;

	SetToNull(false) ;

	return true ;
}

//##ModelId=3F90F92C0239
bool CQF_Field::SetString(const char* szValue)
{
	// 判断类型和定义长度是否合法
	assert (m_iType == QF_STRING) ;
	if (m_iType != QF_STRING)
	{
		assert(false) ;
		return false;
	}

	// 如果传入的值为空,则设为空值
	if (szValue == NULL)
	{
		SetToNull() ;
	}
	// 否则,拷贝字符串
	else
	{

		if (m_pValue)
		{
			delete[] ((char *)m_pValue) ;
		}

		if (m_uiLength > 0)
		{
			// 申请内存
			m_pValue = new char[m_uiLength] ;

			// 拷贝数据
			if (strlen(szValue) < m_uiLength)
				strcpy((char*)m_pValue, szValue) ;
			else
			{
				// 截断复制，末尾设为0
				strncpy((char*)m_pValue, szValue, m_uiLength - 1) ;
				((char*)m_pValue)[m_uiLength - 1 ] = '\0' ;
			}
		}
		else
		{
			// 申请内存
			m_pValue = new char[strlen(szValue) + 1] ;
		
			// 拷贝数据
			strcpy((char*)m_pValue, szValue) ;
		}

		SetToNull(false) ;
	}

	return true ;
}

//##ModelId=3F90F92C023B
bool CQF_Field::SetValueAsString(const char* szValueString)
{
	assert(szValueString) ;
	if (!szValueString)
		return false ;

	assert(strlen(szValueString) > 0) ;
	if (strlen(szValueString) == 0)
		return false ;

	switch (m_iType)
	{
		case QF_INTEGER:	SetInt	 ( atoi (szValueString) ) ;			break ;
		case QF_DOUBLE	:	SetDouble( atof (szValueString)) ;			break ;
		case QF_STRING	:	SetString(szValueString) ;					break ;
		case QF_BOOL :
			if (strcmp(szValueString, "TRUE") == 0)
				SetBool(true) ;
			else if (strcmp(szValueString, "FALSE") == 0)
				SetBool(false) ;
			else
			{
				assert(false);
				return false ;
			}
			break ;

		case QF_BINARY :
			{
				// 首先申请足够长度的buffer
/*				char* pbuffer = new char [strlen(szValueString)] ;

				// 进行Base64解码
				int size = QF_DecodeBase64(szValueString,(unsigned char *)pbuffer, strlen(szValueString) ) ;

				// 将解码后的二进制数据写入databuffer
				IQF_DataBuffer* pdatabuffer = (IQF_DataBuffer*) m_pValue ;
				pdatabuffer->SetSize(size) ;
				memcpy(pdatabuffer->GetBufferPtr(),pbuffer,size) ;

				delete[] pbuffer ;		
*/				
				assert(false);
				break ;
				
			}				
		default	:
			assert (false) ;
			return false ;
	}

	SetToNull(false) ;
	return true ;
}

//##ModelId=3F90F92C023D
bool CQF_Field::IsNull()
{
	if (m_iFlags & 0x2)
		return true;
	else
		return false ;
}

//##ModelId=3F90F92C023E
bool CQF_Field::SetToNull(bool bIsNull)
{
	if (bIsNull)
	{
		if (m_iFlags & 0x1)
			m_iFlags |= 0x2 ;
		else
			return false ;
	}
	else
		m_iFlags &= ~0x2 ;

	return true ;
}

//##ModelId=3F910CAD00FD
void CQF_Field::Release()
{
	delete this ;
}

//##ModelId=3F9E33E0028F
int CQF_Field::GetExtType()
{
	return m_iExtType; 
}

//##ModelId=3F9E33E002AE
void CQF_Field::SetExtType(int ExtType)
{
	m_iExtType = ExtType ;
}

//##ModelId=3FA4B94603E5
IQF_Field& CQF_Field::operator=(const IQF_Field& right)
{
	// 首先清除本身的所有数据
	Clear() ;

	IQF_Field* pright = (IQF_Field*) &right ;

	this->SetName (pright->GetName ()) ;
	this->SetCaption (pright->GetCaption ()) ;
	this->SetDesc (pright->GetDesc ()) ;
 	this->SetDefLength (pright->GetDefLength ()) ; // SetLength before SetType
	this->SetType(pright->GetType ()) ;
	this->SetExtType (pright->GetExtType ()) ;
	this->SetStereoType (pright->GetStereoType ()) ;
	this->SetNullable (pright->IsNullable ()) ;
//	this->SetToBeArchive(pright->IsToBeArchive()) ;
	this->SetToNull (pright->IsNull ()) ;
	if (!this->IsNull ())
	{
		switch(this->GetType ())
		{
			case QF_INTEGER : this->SetInt (pright->GetInt ()) ; break ;
			case QF_BOOL	 : this->SetBool (pright->GetBool ()) ; break ;
			case QF_DOUBLE  : this->SetDouble (pright->GetDouble ()) ; break ;
			case QF_STRING  : this->SetString (pright->GetString ()) ; break ;
	//		case QF_BINARY	 : *(this->GetBinary ()) = *(pright->GetBinary()) ; break ;
	//		case QF_ARRAY	 : *(this->GetArray ()) = *(pright->GetArray()) ; break ;
	//		case QF_PROPERTYSET: *(this->GetPropertySet()) = *(pright->GetPropertySet()) ; break ;
			default : assert (false) ;
		}
	}
	
	return *this ;
}

//##ModelId=3FA4B94700A9
int CQF_Field::operator==(const IQF_Field& right)
{
	int is_equal = 0 ;
	IQF_Field* pright = (IQF_Field*) &right ;

	// 首先判断元数据是否相等
	if ((strcmp(this->GetName (), pright->GetName ()) == 0) &&
		(strcmp(this->GetCaption (), pright->GetCaption ()) == 0) &&
		(strcmp(this->GetDesc (), pright->GetDesc ()) == 0) &&
		(strcmp(this->GetStereoType (), pright->GetStereoType ()) == 0) &&
		(this->GetType () == pright->GetType ()) &&
		(this->GetExtType () == pright->GetExtType ()) &&
		(this->IsNullable () == pright->IsNullable ()) &&
//		(this->IsToBeArchive() == pright->IsToBeArchive ()) &&
		(this->GetDefLength () == pright->GetDefLength ()) &&
		(this->IsNull () == pright->IsNull ()))
	{
		// 如果元数据相同，并且数据相同，则两对象相同
		if(IsNull())
			is_equal = 1 ;
		else
		{
			switch(this->GetType ())
			{
				case QF_INTEGER : 
					{
						if (this->GetInt () == pright->GetInt ()) 
							is_equal = 1 ;

						break ;
					}

				case QF_BOOL : 
					{
						if (this->GetBool() == pright->GetBool ()) 
							is_equal = 1 ;
						
						break ;
					}

				case QF_DOUBLE  : 
					{
						if (QF_ISEQUAL_DBL(this->GetDouble () , pright->GetDouble ())) 
							is_equal = 1 ;

						break ;
					}

				case QF_STRING  : 
					{
						if (strcmp(this->GetString () , pright->GetString ()) == 0) 
							is_equal = 1 ;

						break ;
					}

	/*			case QF_BINARY  : 
					{
						if (*(this->GetBinary()) == *(pright->GetBinary ())) 
							is_equal = 1 ;
						
						break ;
					}
					
				case QF_ARRAY  : 
					{
						if (*(this->GetArray()) == *(pright->GetArray ())) 
							is_equal = 1 ;
						
						break ;
					}
					
				case QF_PROPERTYSET  : 
					{
						if (*(this->GetPropertySet()) == *(pright->GetPropertySet ())) 
							is_equal = 1 ;
						
						break ;
					}
	*/				
				default : 
					{
						assert (false) ;
					}
			} // switch
		} // if (IsNull()) 
	}
	
	return is_equal ;
}

//##ModelId=3FA4B9470154
int CQF_Field::operator!=(const IQF_Field& right)
{
	return !(*this == right) ;
}

//##ModelId=3FA4B9CB02B0
void CQF_Field::Clear()
{
	// 删除所有数据
	if (strlen(m_szName) > 0)
		delete[] m_szName ;

	if (strlen(m_szStereoType) > 0)
		delete[] m_szStereoType ;

	if (strlen(m_szCaption) > 0)
		delete[] m_szCaption ;

	if (strlen(m_szDesc) > 0)
		delete[] m_szDesc ;

	switch (m_iType)
	{
		case QF_INTEGER:	delete (int*) m_pValue ;	break ;
		case QF_BOOL:		delete (char*) m_pValue ;	break ;
	//	case QF_EXPRESSION :
		case QF_DOUBLE	:	delete (double*) m_pValue ;	break ;
	//	case QF_REFERENCE :
		case QF_STRING	:	delete[] (char*) m_pValue ;	break ;
		case QF_BINARY	:	((IQF_DataBuffer*) m_pValue)->Release () ;	break ;
	//	case QF_ARRAY	:	((IQF_Array*) m_pValue)->Release () ;	break ;
	//	case QF_PROPERTYSET	:	((IQF_PropertySet*) m_pValue)->Release () ;	break ;
	//	case QF_TIME	:	delete (SQF_Time*) m_pValue ;	break ;
		default:
			break;
	}

	// 初始化为最初状态
	Init() ;

}

//##ModelId=3FA4BA0B0070
void CQF_Field::Init()
{
    m_szName = "" ;
    m_iType = QF_UNDEFINED ;
    m_iExtType = QF_UNDEFINED ;
    m_szStereoType = "" ;
    m_uiLength = 0 ;
    m_szCaption = "" ;
    m_szDesc = "" ;
	m_pValue = 0 ;

	m_iFlags = 0x77 ;
}

//##ModelId=4042A6D103E7
bool CQF_Field::GetBool()
{
	assert (m_iType == QF_BOOL) ;
	assert (!(m_iFlags & 0x2)) ;
	assert (m_pValue) ;
	
	bool b_val = false ; 
	
	// 如果类型不对，或还未被设置，则返回false 。
	// 如果为空，则返回false
	
	if ((m_iType == QF_BOOL) &&
		!(m_iFlags & 0x2) &&
		(m_pValue != NULL))
	{
		if (* ((char*) m_pValue )) 
			b_val = true ;
		else
			b_val = false ;
	}
	
	return b_val ;
}

//##ModelId=4042A6E40119
bool CQF_Field::SetBool(bool bValue)
{
	assert (m_iType == QF_BOOL) ;
	
	if (m_iType != QF_BOOL) 
		return false;
	
	// 如果还未申请内存，则申请
	if (m_pValue == NULL)
		m_pValue = new char ;
	
	* ( (char*) m_pValue ) = bValue ;
	
	SetToNull(false) ;
	
	return true ;
}

//##ModelId=405AB05A014D
bool CQF_Field::IsDeletable()
{
	if (m_iFlags & 0x20)
		return true ;
	else
		return false ;
}

//##ModelId=405AB0A20381
bool CQF_Field::IsUpdatable()
{
	if (m_iFlags & 0x10)
		return true ;
	else
		return false ;
}

//##ModelId=405AB0740341
bool CQF_Field::IsIndexable()
{
	if (m_iFlags & 0x4)
		return true ;
	else
		return false ;
}

//##ModelId=405AB08E02F4
bool CQF_Field::IsIndex()
{
	if (m_iFlags & 0x8)
		return true ;
	else
		return false ;
}

//##ModelId=405AB1040076
bool CQF_Field::SetDeletable(bool bDeletable)
{
	if (bDeletable)
		m_iFlags |= 0x20 ;
	else
		m_iFlags &= ~0x20 ;
	
	return true ;
}

//##ModelId=405AB17902DB
bool CQF_Field::SetUpdatable(bool bUpdatable)
{
	if (bUpdatable)
		m_iFlags |= 0x10 ;
	else
		m_iFlags &= ~0x10 ;

	return true ;
}

//##ModelId=405AB119023C
bool CQF_Field::SetIndexable(bool bIndexable)
{
	if (bIndexable)
		m_iFlags |= 0x4 ;
	else
		m_iFlags &= ~0x4 ;

	return true ;
}

//##ModelId=405AB18F00A9
bool CQF_Field::SetToBeIndex(bool bToBeIndex)
{
	if (bToBeIndex)
	{
		if (m_iFlags & 0x4)
			m_iFlags |= 0x8 ;
		else
			return false ;
	}
	else
		m_iFlags &= ~0x8 ;

	return true ;
}

//##ModelId=40BC28F30316
bool CQF_Field::SetDefLength(int iDefLength)
{
	if (iDefLength < 0 || m_uiLength > 0)
	{
		assert(false) ;
		return false ;
	}

	m_uiLength = iDefLength ;
	return true ;
}

//##ModelId=40BC28F30318
int CQF_Field::GetDefLength()
{
	return m_uiLength ;
}

QF_END_NAMESPACE
