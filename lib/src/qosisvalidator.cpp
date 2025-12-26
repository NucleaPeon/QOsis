#include "qosisvalidator.h"

using namespace QOSIS;

QOsisValidator::QOsisValidator() :
    QOsisCommons("")
{

}

QOsisValidator::QOsisValidator(const QString path) :
    QOsisCommons(path)
{

}

QOsisValidator::~QOsisValidator()
{

}

int QOsisValidator::validateXml()
{
    return QOSIS::ENUMS::Validation::OK;
}
