#include <QF_config_internal.h>
#include "CQF_DataBuffer.h"

QF_BEGIN_NAMESPACE(QF)


IQF_DataBuffer* QF_CreateDataBufferObject(int iSize) 
{
	IQF_DataBuffer* p = new CQF_DataBuffer() ;
	assert(p) ;

	if (p)
	{
		// 设置缓冲区大小，如果不成功，则返回null，并删除CQF_DataBuffer对象
		bool success = p->SetSize (iSize) ;
		if (!success)
		{
			delete p ;
			p = NULL ;
		}
	}

	return p ;
}

QF_END_NAMESPACE
