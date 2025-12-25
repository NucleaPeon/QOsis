#ifndef QOSISEXPORTER_H
#define QOSISEXPORTER_H

#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#include "qosiscommons.h"

namespace QOSIS {

class QOsisExporter : public QOsisCommons {
public:
    explicit QOsisExporter();
    QOsisExporter(const QString path);
    ~QOsisExporter();

};

}

#endif
