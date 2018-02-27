#ifndef QTXML_GLOBAL_H
#define QTXML_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef QTXML_LIB
# define QTXML_EXPORT Q_DECL_EXPORT
#else
# define QTXML_EXPORT Q_DECL_IMPORT
#endif

#endif // QTXML_GLOBAL_H
