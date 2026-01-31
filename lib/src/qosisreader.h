#ifndef QOSISREADER_H
#define QOSISREADER_H

#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>
#include <QtCore/QByteArray>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QStringRef>

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QJsonArray>
#include <QtCore/QXmlStreamReader>


#include "qosis.h"
#include "qosiscommons.h"
#include "qosisvalidator.h"

using namespace QOSIS;
using namespace QOSIS::Globals;

namespace QOSIS {

class QOsisCommons;

const QString HEADER = QString("header");
const QStringRef HEADER_REF = QStringRef(&HEADER);

const QString OSISID = QString("osisID");
const QStringRef OSISID_REF = QStringRef(&OSISID);

/*!
 * \brief The QOsisReader class takes a path and reads contents
 */
class QOsisReader : public QOsisCommons {
public:
    explicit QOsisReader();
    QOsisReader(const QString path);
    ~QOsisReader();

    /*!
     * \brief initReader Call this when class is set up correctly
     */
    void initReader();
    QXmlStreamReader* reader();
    bool validate(); // Creates a QOsisValidator, validates against schema and returns bool.
    OsisStructure* getOsisData();

private:
    void parseXml();
    void processXml(QStringRef tagname);
    const QString _schema = QOSIS::Globals::XML_NAMESPACE;
    QXmlStreamReader* _reader;
    QList<QStringRef> _tags;
    OsisStructure* _data;
};

}

#endif
