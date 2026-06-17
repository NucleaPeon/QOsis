#ifndef QOSISWRITER_H
#define QOSISWRITER_H
#include <QtCore/QtGlobal>
#if QT_VERSION < 6
#include <QtXmlPatterns/QXmlSchema>
#include <QtXmlPatterns/QXmlSchemaValidator>
#endif

#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#include "qosiscommons.h"

namespace QOSIS {

class QOsisWriter : public QOsisCommons {
public:
    explicit QOsisWriter();
    QOsisWriter(const QString path);
    ~QOsisWriter();


private:
    QString _path;
};

}

#endif
