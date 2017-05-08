#include <qf_config_internal.h>
#include "CQF_Field.h"

QF_BEGIN_NAMESPACE(QF)

IQF_Field* QF_CreateFieldObject() 
{
	IQF_Field* p = new CQF_Field ;
	assert(p) ;

	return p ;
}

QF_END_NAMESPACE
