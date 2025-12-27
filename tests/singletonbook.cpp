#include "singletonbook.h"
#include <QGlobalStatic>

Q_GLOBAL_STATIC(myClass,uniqueInstance)

BibleSingleton::BibleSingleton(QObject *parent)
{
    Q_UNUSED(parent);
}

BibleSingleton* BibleSingleton::getInstance()
{
    return uniqueInstance;
}

BibleSingleton::~BibleSingleton()
{

}

void BibleSingleton::setOsisStructure(OsisStructure *osis)
{
    this->_ostruct = osis;
}

OsisStructure *BibleSingleton::osis()
{
    if (this->_meta == NULL || this->_ostruct == NULL) { return NULL; }
    return this->_ostruct;
}

void BibleSingleton::initOsis(QString path)
{
    this->_meta = new QOsis(path);
    this->_ostruct = this->_meta->reader()->getOsisData();
}

QOsis *BibleSingleton::meta()
{
    return this->_meta;
}

