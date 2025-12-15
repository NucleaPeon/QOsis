#ifndef QOSISREADER_H
#define QOSISREADER_H

#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#include <QtCore/QByteArray>
#include <QtCore/QFile>

#include "qosiscommons.h"

class QOsisReader : public QOsisCommons {
public:
    explicit QOsisReader();
    QOsisReader(const QString path);
    ~QOsisReader();

    QByteArray read();

private:
};

#endif
