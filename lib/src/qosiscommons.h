#ifndef QOSISCOMMONS_H
#define QOSISCOMMONS_H

#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QString>

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "qosisglobals.h"

namespace QOSIS {

class QOsisCommons {
public:
    QOsisCommons(const QString path);
    const QString path();
    bool isValidPath();
    void setPath(const QString path);
    QFile* file();

private:
    void processPath();
    QString _path = NULL;
    QFile* _file;
};

}


#endif
