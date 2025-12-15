#ifndef QOSISWRITER_H
#define QOSISWRITER_H

#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

class QOsisWriter {
public:
    explicit QOsisWriter();
    QOsisWriter(const QString path);
    ~QOsisWriter();

private:
    QString _path = NULL;
};

#endif
