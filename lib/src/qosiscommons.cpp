#include "qosiscommons.h"

QOsisCommons::QOsisCommons(const QString path) :
    _path(path)
{

}

const QString QOsisCommons::path()
{
    return this->_path;
}

bool QOsisCommons::isValidPath()
{
    return (! this->_path.isEmpty() && ! this->_path.isNull()); // TODO: also check if file or directory
}
