
/********************************************************************
filename: 	QF_Config.h
author:		Ling Song
date: 		ÈýÔÂ 2017
*********************************************************************/
#ifndef IQF_Config_h__
#define IQF_Config_h__

#if ((defined(_MSC_VER) || defined(_WIN32_WCE)) && !defined(GISE_STATIC_LIBS)) || (defined(__HP_aCC) && defined(__HP_WINDLL))
#   define QF_DECLSPEC_EXPORT __declspec(dllexport)
#   define QF_DECLSPEC_IMPORT __declspec(dllimport)
#elif defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x550)
#   define QF_DECLSPEC_EXPORT __global
#   define QF_DECLSPEC_IMPORT
#else
#   define QF_DECLSPEC_EXPORT /**/
#   define QF_DECLSPEC_IMPORT /**/
#endif

#ifdef QF_API_EXPORTS
#   define QF_API QF_DECLSPEC_EXPORT
#else
#   define QF_API QF_DECLSPEC_IMPORT
#endif


#undef QF_BEGIN_NAMESPACE
#undef QF_END_NAMESPACE
#undef QF_USING
#if (__GNUC__ == 2) && (__GNUC_MINOR__ < 9)
#	define QF_BEGIN_NAMESPACE(x)
#	define QF_END_NAMESPACE
#	define QF_USING(x)
#else
#	define QF_BEGIN_NAMESPACE(ns) namespace ns{
#	define QF_END_NAMESPACE }
#	define QF_USING(ns) using ns
#endif

#ifndef  SAVE_DELETE
#define SAVE_DELETE(ptr) \
    if (ptr)              \
    {                       \
        delete ptr;     \
        ptr = NULL;    \
    }
#endif


#endif // IQF_Config_h__

