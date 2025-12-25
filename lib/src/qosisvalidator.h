#ifndef QOSISVALIDATOR_H
#define QOSISVALIDATOR_H

#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#include "qosis.h"
#include "qosiscommons.h"
#include "qosisreader.h"

using namespace QOSIS;

namespace QOSIS {

/*!
 * \brief The QOsisValidator class handles validating the xml for OSIS 2.1 format.
 *
 * Validation takes an XML document and based on the outer-most tag, will verify
 * all inner tags are legitamitely declared and valid within their outer tag and
 * recursively validate until there are no more inner tags and no more next tags
 * to check.
 *
 *
 */

class QOsisValidator : public QOsisCommons {
public:
    explicit QOsisValidator();
    QOsisValidator(const QString path);
    ~QOsisValidator();

    int validateXml();

private:
    QOsisReader *reader;
};

}

#endif // QOSISVALIDATOR_H
