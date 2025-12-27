#include "test_xml_reader.h"

void TestXmlReader::initTestCase()
{
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
    QVERIFY(reader->reader() != NULL);
    qDebug() << reader->reader()->hasError() << reader->reader()->errorString();
    QVERIFY(! reader->reader()->hasError());
    OsisStructure* data = reader->getOsisData();
    qDebug() << data->bookCount() << "Books";
    qDebug() << data->chapterCount() << "Chapters";
    qDebug() << data->verseCount() << "Verses";
//    QVERIFY(! reader->reader()->atEnd());
//    QByteArray data = reader->read();
//    QVERIFY(! data.isEmpty());
}

void TestXmlReader::cleanupTestCase()
{
    delete this->meta;
}
