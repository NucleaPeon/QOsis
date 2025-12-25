#ifndef QOSISCOMMONS_H
#define QOSISCOMMONS_H

#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#include <QtCore/QFile>
#include <QtCore/QDir>

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
