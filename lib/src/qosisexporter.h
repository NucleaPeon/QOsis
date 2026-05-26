#ifndef QOSISEXPORTER_H
#define QOSISEXPORTER_H

#include "qosiscommons.h"

#include <QtCore/QHash>
#include <QtCore/QDataStream>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QByteArray>

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
    static void writeJsonFile(const QString path, QOsisStructure* st, int compression = 0);

    int compressionLevel();
    void setCompressionLevel(int compress);

    static QJsonObject toJson(QOsisStructure* st);

private:
    int _compression;

};

}

#endif
