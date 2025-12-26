#ifndef QOSISREADER_H
#define QOSISREADER_H

#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#include <QtCore/QByteArray>
#include <QtCore/QFile>

#include "qosis.h"
#include "qosiscommons.h"

using namespace QOSIS;
using namespace QOSIS::Globals;

namespace QOSIS {

class QOsisCommons;

class QOsisReader : public QOsisCommons {
public:
    explicit QOsisReader();
    QOsisReader(const QString path);
    ~QOsisReader();

    QByteArray read();

private:
    const QString schema = "";
};

}

#endif
