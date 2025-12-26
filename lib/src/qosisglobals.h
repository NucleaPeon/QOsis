#ifndef QOSISGLOBALS_H
#define QOSISGLOBALS_H



#include "version.h"

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

}



#endif
