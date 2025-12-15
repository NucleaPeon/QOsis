#ifndef QOSISVALIDATOR_H
#define QOSISVALIDATOR_H

#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#include "qosiscommons.h"
#include "qosisreader.h"

class QOsisValidator : public QOsisCommons {
public:
    explicit QOsisValidator();
    QOsisValidator(const QString path);
    ~QOsisValidator();

private:
    QOsisReader *reader;
};

#endif // QOSISVALIDATOR_H
