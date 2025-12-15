#ifndef QOSIS_GLOBAL_H
#define QOSIS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QOSIS_LIBRARY)
# define QOSISSHARED_EXPORT Q_DECL_EXPORT
#else
# define QOSISSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QOSIS_GLOBAL_H
