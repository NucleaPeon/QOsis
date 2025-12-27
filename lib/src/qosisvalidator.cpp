#include "qosisvalidator.h"

using namespace QOSIS;

QOsisValidator::QOsisValidator() :
    QOsisCommons("")
{

}

QOsisValidator::QOsisValidator(const QString path) :
    QOsisCommons(path)
{

}

QOsisValidator::~QOsisValidator()
{

}

int QOsisValidator::validateXml()
{
    return QOSIS::ENUMS::Validation::OK;
}

void QOsisValidator::setupSchema(const QString schema)
{
    QFile* f = new QFile(schema);
    f->open(QIODevice::ReadOnly);
    QByteArray xsd = f->readAll();
    f->close();
//    _schema = new QXmlSchema();
//    _schema->load(xsd);
}
