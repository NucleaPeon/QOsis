#ifndef QOSISCOMMONS_H
#define QOSISCOMMONS_H

#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

class QOsisCommons {
public:
    QOsisCommons(const QString path);
    const QString path();
    bool isValidPath();

private:
    QString _path = NULL;
};

#endif
