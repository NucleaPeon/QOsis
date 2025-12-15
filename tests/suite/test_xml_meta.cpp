#include "test_xml_meta.h"

void TestXmlMeta::initTestCase()
{
    qDebug() << "initializing test case";
    this->meta = new QOsis();
}

void TestXmlMeta::testGetters()
{
    QVERIFY(this->meta->reader() != NULL);
    QVERIFY(this->meta->writer() != NULL);
    QVERIFY(this->meta->exporter() != NULL);
    QVERIFY(this->meta->importer() != NULL);
}

void TestXmlMeta::cleanupTestCase()
{
    delete this->meta;
}
