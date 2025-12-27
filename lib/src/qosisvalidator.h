#ifndef QOSISVALIDATOR_H
#define QOSISVALIDATOR_H

#include "qosisglobals.h"
#include "qosiscommons.h"

#include <QtXmlPatterns/QXmlSchema>
#include <QtXmlPatterns/QXmlSchemaValidator>


namespace QOSIS {

class QOsisReader;

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
    void setupSchema(const QString schema = QOSIS::Globals::XML_NAMESPACE);
    QXmlSchema* _schema;
};

}

#endif // QOSISVALIDATOR_H
