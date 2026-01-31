#ifndef QOSISJSON_H
#define QOSISJSON_H

#include "qosisglobals.h"

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QJsonArray>
#include <QtCore/QXmlStreamReader>

#include "qosisreader.h"

namespace QOSIS {

/*!
 * \brief The QOsisJson class is a json format based on osisCore2.1.1 that avoids being xml.
 *
 * Once the xml is read and the json populated, this class gives hints as to what exists
 * within the osis content (books, chapters, verses, etc) which are easily accessible.
 *
 */
class QOsisJson : public QJsonDocument {

public:
    explicit QOsisJson();
    QOsisJson(const QString path);

    void process(QOsisReader *reader);

private:
    QJsonObject store(QXmlStreamReader *reader, QList<QStringRef> tags);
    QString _path;
    QJsonObject _root;
};

}

#endif
