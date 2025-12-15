#ifndef QOSISVALIDATOR_H
#define QOSISVALIDATOR_H

#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#include "qosiscommons.h"

class QOsisValidator : QOsisCommons {
public:
    explicit QOsisValidator();
    QOsisValidator(const QString path);
    ~QOsisValidator();

private:
    QString _path = NULL;

};

#endif // QOSISVALIDATOR_H
