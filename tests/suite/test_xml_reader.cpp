#include "test_xml_reader.h"

void TestXmlReader::initTestCase()
{
    qDebug() << "initializing test case";
    this->meta = new QOsis();
}

void TestXmlReader::testConstructors()
{
    QOsisReader* reader = new QOsisReader("");
    QVERIFY(! reader->isValidPath());
    reader = NULL;
    reader = new QOsisReader(TEST_FILE);
    QVERIFY(reader->isValidPath());
    delete reader;
}

void TestXmlReader::testReadingFile()
{
    this->meta->setPath(TEST_FILE);
    QOsisReader* reader = new QOsisReader(TEST_FILE);
    QByteArray data = reader->read();
    QVERIFY(! data.isEmpty());
    delete reader;
}

void TestXmlReader::cleanupTestCase()
{
    delete this->meta;
}
