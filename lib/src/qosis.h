#ifndef QOSIS_H
#define QOSIS_H

#include <QtCore/QString>

#include "version.h"
#include "qosiscommons.h"
#include "qosisreader.h"
#include "qosiswriter.h"
#include "qosisvalidator.h"
#include "qosisimporter.h"
#include "qosisexporter.h"

using namespace QOSIS::Library::Version;

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

};

#endif // QOSIS_H
