#include "qosis.h"

QOsis::QOsis() :
    QOsisCommons("")
{

}

QOsis::QOsis(const QString path) :
    QOsisCommons(path)
{
}

QOsis::~QOsis()
{

}

QOsisReader *QOsis::reader()
{
    return new QOsisReader(path());
}

QOsisWriter *QOsis::writer()
{
    return new QOsisWriter(path());
}

QOsisExporter *QOsis::exporter()
{
    return new QOsisExporter(path());
}

QOsisImporter *QOsis::importer()
{
    return new QOsisImporter(path());
}

QOsisValidator *QOsis::validator()
{
    return new QOsisValidator(path());
}

