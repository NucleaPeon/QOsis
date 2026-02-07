#ifndef QOSISMETA_H
#define QOSISMETA_H

#include "qosisglobals.h"
#include "qosis.h"

namespace QOSIS {

class QOsisReader;
class QOsisValidator;
class QOsisWriter;
class QOsisExporter;
class QOsisImporter;


/*!
 * \brief The QOsis class is the meta OSIS class that handles all areas of osis file work
 *
 * From here, you can access the xml reader, writer, validator, importer and exporter classes.
 * By default, constructors can be empty and required values set later, or you can construct
 * objects with those required values.
 */
class QOsis : public QOsisCommons {
public:
    explicit QOsis();
    QOsis(const QString path);
    ~QOsis();

    QOsisReader* reader();
    QOsisWriter* writer();

    QOsisExporter* exporter();
    QOsisImporter* importer();

    QOsisValidator* validator();

private:
    QOsisReader* _reader;
    QOsisWriter* _writer;
    QOsisExporter* _exporter;
    QOsisImporter* _importer;
    QOsisValidator* _validator;


};

}


#endif
