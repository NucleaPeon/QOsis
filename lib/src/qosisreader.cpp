#include "qosisreader.h"
#include <QtCore/QDebug>

using namespace QOSIS;

QOsisReader::QOsisReader() :
    QOsisCommons("")
{

}

QOsisReader::QOsisReader(const QString path) :
    QOsisCommons(path)
{
    this->initReader();
}

QOsisReader::~QOsisReader()
{

}

void QOsisReader::initReader()
{
    // Read when conditions allow
    if (this->isValidPath()) {
        if (_reader == NULL) {
            QFile* f = this->file();
            f->open(QIODevice::ReadOnly);
            QByteArray arr = f->readAll();
            f->close();

            _reader = new QXmlStreamReader(arr);
            _reader->setNamespaceProcessing(false);
            this->parseXml();
        }
    }
}

QXmlStreamReader *QOsisReader::reader()
{
    return _reader;
}

bool QOsisReader::validate()
{
    QOsisValidator v = QOsisValidator(this->path());
    return v.validateXml() == QOSIS::ENUMS::Validation::OK;
}

void QOsisReader::parseXml()
{
    QJsonObject root = QJsonObject();
//    while(! _reader->atEnd()) {
//        QXmlStreamReader::TokenType type = _reader->readNext();
//        if (_reader->isStartElement()) {
//            QJsonObject o = QJsonObject();
//            root.insert(_reader->name().toString(), o);
//            foreach(QXmlStreamAttribute attr, _reader->attributes()) {
//                o.insert(attr.name().toString(), attr.value().toString());
//            }
//        }

//    qDebug() << obj;
}
