/********************************************************************
	filename: 	qf_config_internal.h
	author:		Ling Song
	date: 		ÈýÔÂ 2017
*********************************************************************/
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

inline bool QF_ISEQUAL_DBL(double d1, double d2) { return (d1 > d2) ? (d1 - d2 < 1.0e-10) : (d2 - d1 < 1.0e-10); }

inline bool QF_ISVALID_BASIC_DATATYPE(int iType)
{
    return ((iType == QF_DataType_Integer) ||
        (iType == QF_DataType_Double) ||
        (iType == QF_DataType_String) ||
        (iType == QF_DataType_Bool));
}

inline bool QF_ISVALID_DATATYPE(int iType)
{
    return QF_ISVALID_BASIC_DATATYPE(iType);
}


#if !defined(SAG_COM) && (!defined(WINAPI_FAMILY) || WINAPI_FAMILY==WINAPI_FAMILY_DESKTOP_APP) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#  define QF_OS_WIN32
#  define QF_OS_WIN64
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#  if defined(WINCE) || defined(_WIN32_WCE)
#    define QF_OS_WINCE
#  elif defined(WINAPI_FAMILY)
#    ifndef WINAPI_FAMILY_PC_APP
#      define WINAPI_FAMILY_PC_APP WINAPI_FAMILY_APP
#    endif
#    if defined(WINAPI_FAMILY_PHONE_APP) && WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
#      define QF_OS_WINPHONE
#      define QF_OS_WINRT
#    elif WINAPI_FAMILY==WINAPI_FAMILY_PC_APP
#      define QF_OS_WINRT
#    else
#      define QF_OS_WIN32
#    endif
#  else
#    define QF_OS_WIN32
#  endif
#elif defined(__linux__) || defined(__linux)
#  define QF_OS_LINUX
#endif

#if defined(QF_OS_WIN32) || defined(QF_OS_WIN64) || defined(QF_OS_WINCE) || defined(QF_OS_WINRT)
#  define QF_OS_WIN
#endif


#endif // qf_config_internal_h__
