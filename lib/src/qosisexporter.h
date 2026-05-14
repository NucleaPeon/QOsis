#ifndef QOSISEXPORTER_H
#define QOSISEXPORTER_H

#include "qosiscommons.h"

#include <QtCore/QHash>
#include <QtCore/QDataStream>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>


namespace QOSIS {

class QOsisExporter : public QOsisCommons {
public:
    explicit QOsisExporter();
    QOsisExporter(const QString path);
    ~QOsisExporter();

    void writeJsonFile(QOsisStructure* st);
    void readJsonFile();

    QJsonObject toJson(QOsisStructure* st);

};

}

#endif
