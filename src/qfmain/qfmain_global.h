#pragma once

#include <QtCore/qglobal.h>

#ifndef QT_STATIC
# if defined(QFMAIN_LIB)
#  define QFMAIN_EXPORT Q_DECL_EXPORT
# else
#  define QFMAIN_EXPORT Q_DECL_IMPORT
# endif
#else
# define QFMAIN_EXPORT
#endif
