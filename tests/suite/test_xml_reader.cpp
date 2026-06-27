#include "test_xml_reader.h"

void TestXmlReader::initTestCase()
{
    this->meta = BibleSingleton::getInstance()->meta();
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
    QVERIFY(! reader->reader()->hasError());
    QOsisStructure* data = BibleSingleton::getInstance()->osis();
    QVERIFY(data->title() != QString());
    QVERIFY(data->title() == "King James Version");
    QVERIFY(data->bookCount() > 0);
    QVERIFY(data->chapterCount() > 0);
    QVERIFY(data->verseCount() > 0);
    QVERIFY(data->bookCount() == 66); // KJV 66 books in the bible
}

void TestXmlReader::testDebug()
{
    // Not working as expected, still giving pointer addresses.
#ifdef QT_DEBUG
    QOsisStructure* structure = BibleSingleton::getInstance()->osis();
    qDebug() << structure;
    qDebug() << structure->book("Gen");
    qDebug() << structure->book("Gen")->chapter(1);
    qDebug() << structure->book("Gen")->chapter(1)->verse(1);
#endif

}

void TestXmlReader::testOrdering()
{
    QOsisReader* reader = BibleSingleton::getInstance()->meta()->reader();
    QOsisBook* book;
    foreach(const QString bookname, reader->getOsisData()->books()) {
        // This confirms that our numbering starts at readable, concrete numbers (not 0)
        book = reader->getOsisData()->book(bookname);
        QVERIFY(book->chapter(1)->verseCount() > 0);
        QVERIFY(book->chapter(0) == NULL);
        QOsisChapter* c = book->chapter(1);
        QVERIFY(c->verse(1) != NULL);
        QVERIFY(c->verse(0) == NULL);
    }
}

void TestXmlReader::cleanupTestCase()
{
}
