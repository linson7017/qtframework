
#ifndef MBILOG_EXPORT_H
#define MBILOG_EXPORT_H

#ifdef MBILOG_STATIC_DEFINE
#  define MBILOG_EXPORT
#  define MBILOG_NO_EXPORT
#else
#  ifndef MBILOG_EXPORT
#    ifdef mbilog_EXPORTS
        /* We are building this library */
#      define MBILOG_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define MBILOG_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef MBILOG_NO_EXPORT
#    define MBILOG_NO_EXPORT 
#  endif
#endif

#ifndef MBILOG_DEPRECATED
#  define MBILOG_DEPRECATED __declspec(deprecated)
#endif

#ifndef MBILOG_DEPRECATED_EXPORT
#  define MBILOG_DEPRECATED_EXPORT MBILOG_EXPORT MBILOG_DEPRECATED
#endif

#ifndef MBILOG_DEPRECATED_NO_EXPORT
#  define MBILOG_DEPRECATED_NO_EXPORT MBILOG_NO_EXPORT MBILOG_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MBILOG_NO_DEPRECATED
#    define MBILOG_NO_DEPRECATED
#  endif
#endif

#endif
