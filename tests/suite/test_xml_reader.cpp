#include "test_xml_reader.h"

void TestXmlReader::initTestCase()
{
}

void TestXmlReader::testConstructors()
{
    QOsisReader* reader = new QOsisReader("");
    QVERIFY(! reader->isValidPath());
    reader = NULL;
    reader = BibleSingleton::getInstance()->meta()->reader();
    QVERIFY(reader->isValidPath());
}

void TestXmlReader::testReadingFile()
{
    QOsisReader* reader = BibleSingleton::getInstance()->meta()->reader();
    QVERIFY(reader != NULL);
    qDebug() << reader->reader()->hasError() << reader->reader()->errorString();
    QVERIFY(! reader->reader()->hasError());
    OsisStructure* data = BibleSingleton::getInstance()->osis();
    QVERIFY(data->bookCount() > 0);
    QVERIFY(data->chapterCount() > 0);
    QVERIFY(data->verseCount() > 0);
    QVERIFY(data->bookCount() == 66); // KJV 66 books in the bible
}

void TestXmlReader::cleanupTestCase()
{
}
