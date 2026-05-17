#ifndef QOSISIMPORTER_H
#define QOSISIMPORTER_H

#include "qosiscommons.h"

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QFile>

namespace QOSIS {

class QOsisImporter : public QOsisCommons {

public:
    explicit QOsisImporter();
    QOsisImporter(const QString path);
    ~QOsisImporter();

    QOsisStructure* importJsonFile(int compression = -1);

private:
    QOsisStructure* processJson(QJsonDocument doc);
};

}

#endif
