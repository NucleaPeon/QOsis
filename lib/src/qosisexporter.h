#ifndef QOSISEXPORTER_H
#define QOSISEXPORTER_H

#include "qosiscommons.h"

#include <QtCore/QHash>
#include <QtCore/QDataStream>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>


namespace QOSIS {

class QOsisExporter : public QOsisCommons {
public:
    // TODO: A QSetting value will determine default compression
    explicit QOsisExporter();
    QOsisExporter(const QString path);
    ~QOsisExporter();

    /*!
     * \brief writeJsonFile
     * \param st QOsisStructure*
     */
    void writeJsonFile(QOsisStructure* st);

    int compressionLevel();
    void setCompressionLevel(int compress);

    QJsonObject toJson(QOsisStructure* st);

private:
    int _compression;

};

}

#endif
