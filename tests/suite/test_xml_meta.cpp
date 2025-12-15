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
    QVERIFY(this->meta->validator() != NULL);
    // Path will not be valid
    QVERIFY(! this->meta->validator()->isValidPath());
    QVERIFY(! this->meta->reader()->isValidPath());
    QVERIFY(! this->meta->writer()->isValidPath());
    QVERIFY(! this->meta->exporter()->isValidPath());
    QVERIFY(! this->meta->importer()->isValidPath());
}

void TestXmlMeta::cleanupTestCase()
{
    delete this->meta;
}
