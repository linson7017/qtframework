#ifndef qf_config_internal_h__
#define qf_config_internal_h__

#include "qf_config.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>


struct ltstr	
{
    bool operator()(const char* s1, const char* s2) const
    {
        return strcmp(s1, s2) < 0;
    }
};

enum QFDataType
{
    QF_UNDEFINED = 0x00,
    QF_INTEGER = 0x01,
    QF_DOUBLE = 0x02,
    QF_STRING = 0x04,
    //	QF_TIME	= 0x08,
    QF_BINARY = 0x10,
    QF_BOOL = 0x20
};

inline bool QF_ISEQUAL_DBL(double d1, double d2) { return (d1 > d2) ? (d1 - d2 < 1.0e-10) : (d2 - d1 < 1.0e-10); }

inline bool QF_ISVALID_BASIC_DATATYPE(int iType)
{
    return ((iType == QF_INTEGER) ||
        (iType == QF_DOUBLE) ||
        (iType == QF_STRING) ||
        (iType == QF_BINARY) ||
        (iType == QF_BOOL));
}

inline bool QF_ISVALID_DATATYPE(int iType)
{
    return QF_ISVALID_BASIC_DATATYPE(iType);
}

#endif // qf_config_internal_h__
