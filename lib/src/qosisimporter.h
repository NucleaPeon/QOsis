#ifndef QOSISIMPORTER_H
#define QOSISIMPORTER_H

#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#include "qosiscommons.h"

class QOsisImporter : public QOsisCommons {
public:
    explicit QOsisImporter();
    QOsisImporter(const QString path);
    ~QOsisImporter();

};

#endif
