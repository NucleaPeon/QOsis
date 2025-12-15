#include "qosisreader.h"
#include <QtCore/QDebug>
QOsisReader::QOsisReader() :
    QOsisCommons("")
{

}

QOsisReader::QOsisReader(const QString path) :
    QOsisCommons(path)
{
}

QOsisReader::~QOsisReader()
{

}

QByteArray QOsisReader::read()
{
    QFile* f = this->file();
    f->open(QIODevice::ReadOnly);
    QByteArray arr = f->readAll();
    f->close();
    return arr;
}
