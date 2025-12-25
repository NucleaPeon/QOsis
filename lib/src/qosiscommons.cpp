#include "qosiscommons.h"
#include <QtCore/QDebug>

using namespace QOSIS;

QOsisCommons::QOsisCommons(const QString path)
{
    this->setPath(path);
}

const QString QOsisCommons::path()
{
    return this->_path;
}

bool QOsisCommons::isValidPath()
{
    return ! this->_path.isEmpty() && QFile(this->_path).exists();
}

void QOsisCommons::setPath(const QString path)
{
    this->_path = path;
    this->processPath();
}

QFile *QOsisCommons::file()
{
    return this->_file;
}

void QOsisCommons::processPath()
{
    if (isValidPath()) {
        qDebug() << Q_FUNC_INFO << this->path();
        _file = new QFile(this->_path);
    }

}
