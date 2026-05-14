#include "qosisexporter.h"
#include <QtCore/QDebug>

using namespace QOSIS;

QOsisExporter::QOsisExporter() :
    QOsisCommons("")
{

}

QOsisExporter::QOsisExporter(const QString path) :
    QOsisCommons(path)
{

}

QOsisExporter::~QOsisExporter()
{

}

void QOsisExporter::writeJsonFile(QOsisStructure *st)
{
    qDebug() << Q_FUNC_INFO;
    QJsonObject obj = toJson(st);
    QJsonDocument doc = QJsonDocument(obj);

    QFile file(this->path());
    file.write(doc.toJson());
    file.close();

}

void QOsisExporter::readJsonFile()
{
    qDebug() << Q_FUNC_INFO;
}

QJsonObject QOsisExporter::toJson(QOsisStructure *st)
{

}
