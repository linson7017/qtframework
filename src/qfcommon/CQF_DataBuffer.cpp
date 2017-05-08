#include <qf_config_internal.h>
#include "CQF_DataBuffer.h"
#include <string.h>

QF_BEGIN_NAMESPACE(QF)


//##ModelId=3F9CF3D10031
CQF_DataBuffer::CQF_DataBuffer()
{
	m_iSize = 0 ;
	m_pBuffer = (char*) 0 ;
}

//##ModelId=3F9CF3D10032
CQF_DataBuffer::~CQF_DataBuffer()
{
	Clear() ;
}

//##ModelId=3F9CF3D10033
bool CQF_DataBuffer::SetSize(int iSize)
{
/*	bool success = false ;

	// 首先清除现有缓冲区
	Clear() ;

	if (iSize == 0)
	{
		m_iSize = 0 ;
		success = true ;
	}
	else
	{
		m_pBuffer = new char [iSize] ;
		assert(m_pBuffer) ;

		if (m_pBuffer)
		{
			m_iSize = iSize ;

			// 初始化内存
			memset(m_pBuffer,0,m_iSize) ;

			success = true ;
		}
		else
			success = false ; // 内存分配不成功
	}

	return success ;
*/
	if (iSize == m_iSize)
	{
		memset(m_pBuffer,0,m_iSize);
		return true;
	}
	// 首先清除现有缓冲区
	Clear();

	m_iSize = iSize;
	
	if (iSize == 0)
		return true;

	m_pBuffer = new char[iSize];

	if (!m_pBuffer)
	{
		assert(false);
		return false;
	}
	
	memset(m_pBuffer,0,m_iSize);
	return true;
}

//##ModelId=3F9CF3D10035
int CQF_DataBuffer::GetSize()
{
	return m_iSize ;
}

//##ModelId=3F9CF3D10036
char* CQF_DataBuffer::GetBufferPtr()
{
	return m_pBuffer ;
}

//##ModelId=3F9CF3D10037
void CQF_DataBuffer::Release()
{
	delete this ;
}

//##ModelId=3F9CF3D10038
void CQF_DataBuffer::Clear()
{
	if (m_pBuffer)
	{
		delete[] m_pBuffer ;
		m_pBuffer = 0 ;
		m_iSize = 0 ;
	}
}

//##ModelId=3FA4C73200B4
IQF_DataBuffer& CQF_DataBuffer::operator=(const IQF_DataBuffer& right)
{
	IQF_DataBuffer* pright = (IQF_DataBuffer*) &right ;

	this->SetSize (pright->GetSize()) ;
	memcpy(this->GetBufferPtr (), pright->GetBufferPtr (), GetSize()) ;

	return *this ;
}

//##ModelId=3FA4C7320122
int CQF_DataBuffer::operator==(const IQF_DataBuffer& right)
{
	int is_equal = 0 ;
	IQF_DataBuffer* pright = (IQF_DataBuffer*) &right ;

	if (this->GetSize () == pright->GetSize ())
	{
		if (memcmp(this->GetBufferPtr (), pright->GetBufferPtr (), GetSize()) == 0)
			is_equal = true ;
	}

	return is_equal ;
}

//##ModelId=3FA4C732018F
int CQF_DataBuffer::operator!=(const IQF_DataBuffer& right)
{
	return !(*this == right) ;
}

QF_END_NAMESPACE
