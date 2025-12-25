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

namespace QOSIS {

/*!
 * QOSIS::ENUMS namespace contains variables in all upper-case naming conventions
 * that allows readable names for errors/warnings/states without relying on
 * QObject's Q_ENUM() macro to avoid that dependency to keep things simple.
 */
namespace ENUMS {

namespace Validation {

    const static int UNKNOWN_ERROR = -1;
    const static int OK = 0;
    const static int EMPTY_XML = 1;
}

}

namespace Globals {
    // DEV NOTE: This address is no longer in use and is only used as it is defined by the standard.
    // We use a downloaded xsd version to validate the schema.
    const static char* XML_NAMESPACE = "http://www.bibltechnolgologies.net/OSIS/osisCore.2.1.xsd";
}


class QOsisValidator;
class QOsisReader;

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

}

#endif // QOSIS_H
