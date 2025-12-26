#ifndef QOSISWRITER_H
#define QOSISWRITER_H

#include <QtXmlPatterns/QXmlSchemaValidator>
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
    QString _path = NULL;
};

}

#endif
