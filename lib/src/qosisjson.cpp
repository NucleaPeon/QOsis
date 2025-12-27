#include "qosisjson.h"
#include <QtCore/QDebug>

using namespace QOSIS;

QOsisJson::QOsisJson() :
    QJsonDocument(),
    _root(QJsonObject())
{
    this->setObject(_root);
}

QOsisJson::QOsisJson(const QString path) :
    QJsonDocument(),
    _path(path),
    _root(QJsonObject())
{
    this->setObject(_root);
}

void QOsisJson::process(QOsisReader* reader)
{
    QXmlStreamReader *xmlReader = reader->reader();
    QList<QStringRef> tags = QList<QStringRef>();
    QJsonObject lastobj = this->_root;
    while(! xmlReader->atEnd()) {
        switch(xmlReader->tokenType()) {
        case QXmlStreamReader::NoToken:
            xmlReader->readNext();
            return process(reader);
        default:
            QJsonObject o = store(xmlReader, tags);
            lastobj.insert(xmlReader->name().toString(), o);
            lastobj = o;
            xmlReader->readNext();
            break;
        }
    }
}

QJsonObject QOsisJson::store(QXmlStreamReader *reader, QList<QStringRef> tags)
{
    QJsonObject obj;
    const QStringRef name = reader->name();
    tags.push_front(name);

    if (name == "osis") {
        if (tags.front() == "osis") {
            return obj;
        }
        QJsonObject attrs;
        foreach(QXmlStreamAttribute attr, reader->attributes()) {
            attrs.insert(attr.name().toString(), attr.value().toString());
        }
        obj = QJsonObject();
        obj.insert("osis", attrs);
    }
    reader->readNext();
    store(reader, tags);
}
