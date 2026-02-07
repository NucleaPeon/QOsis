#include "qosismeta.h"

using namespace QOSIS;

QOsis::QOsis() :
    QOsisCommons(""),
    _reader(NULL),
    _writer(NULL),
    _importer(NULL),
    _exporter(NULL),
    _validator(NULL)
{

}

QOsis::QOsis(const QString path) :
    QOsisCommons(path),
    _reader(NULL),
    _writer(NULL),
    _importer(NULL),
    _exporter(NULL),
    _validator(NULL)
{
}

QOsis::~QOsis()
{

}

QOsisReader *QOsis::reader()
{
    if (_reader == NULL) {
        _reader = new QOsisReader(path());
    }
    return _reader;
}

QOsisWriter *QOsis::writer()
{
    if (_writer == NULL) {
        _writer = new QOsisWriter(path());
    }
    return _writer;
}

QOsisExporter *QOsis::exporter()
{
    if (_exporter == NULL) {
        _exporter = new QOsisExporter(path());
    }
    return _exporter;
}

QOsisImporter *QOsis::importer()
{
    if (_importer == NULL) {
        _importer = new QOsisImporter(path());
    }
    return _importer;
}

QOsisValidator *QOsis::validator()
{
    if (_validator == NULL) {
        _validator = new QOsisValidator(path());
    }
    return _validator;
}


