#include "test_xml_meta.h"

void TestXmlMeta::initTestCase()
{
    this->meta = new QOsis();
}

void TestXmlMeta::testGetters()
{
    QVERIFY(this->meta->reader() != NULL);
    QVERIFY(this->meta->writer() != NULL);
    QVERIFY(this->meta->exporter() != NULL);
    QVERIFY(this->meta->importer() != NULL);
    QVERIFY(this->meta->validator() != NULL);
    // Path will not be valid when constructed without path
    QVERIFY(! this->meta->isValidPath());
    QVERIFY(! this->meta->validator()->isValidPath());
    QVERIFY(! this->meta->reader()->isValidPath());
    QVERIFY(! this->meta->writer()->isValidPath());
    QVERIFY(! this->meta->exporter()->isValidPath());
    QVERIFY(! this->meta->importer()->isValidPath());
    this->meta->setPath("://kjv.xml");
    QVERIFY(this->meta->isValidPath());
}

void TestXmlMeta::testLoadingOsisFile()
{
    QElapsedTimer timer;
    timer.start();
    BibleSingleton::getInstance()->initOsis("://kjv.xml");
    qDebug() << "Initializing the Osis XML File took" << timer.elapsed() << "milliseconds";
    timer.invalidate();
    timer.start();

    QOsisExporter::writeJsonFile(
                QString("%1/kvj.jsonc").arg(QDir::tempPath()),
                BibleSingleton::getInstance()->meta()->reader()->getOsisData(),
                9
    );

    qDebug() << "Initializing a compressed json version of a loaded osis xml took" << timer.elapsed() << "milliseconds";
    timer.invalidate();
    timer.start();
    QOsisImporter::importJsonFile(
                QString("%1/kvj.jsonc").arg(QDir::tempPath()),
                9
    );
    qDebug() << "Importing a compressed json version took" << timer.elapsed() << "milliseconds";

    timer.invalidate();
    timer.start();
    QOsisExporter::writeJsonFile(
                QString("%1/kvj.json").arg(QDir::tempPath()),
                BibleSingleton::getInstance()->meta()->reader()->getOsisData(),
                0
    );
    qDebug() << "Initializing an uncompressed json version of a loaded osis xml took" << timer.elapsed() << "milliseconds";

    timer.invalidate();
    timer.start();
    QOsisImporter::importJsonFile(
                QString("%1/kvj.json").arg(QDir::tempPath()),
                0
    );
    qDebug() << "Importing an uncompressed json version took" << timer.elapsed() << "milliseconds";
}

void TestXmlMeta::testParentage()
{
    QOsisStructure* st = BibleSingleton::getInstance()->osis();
    QOsisBook* book = st->books().at(0);
    QOsisChapter* chap = book->chapters.at(0);
    QOsisVerse* verse = chap->verses().at(0);

    QVERIFY(verse->parent() == chap);
    QVERIFY(chap->parent() == book);
    QVERIFY(book->parent() == st);

}

void TestXmlMeta::cleanupTestCase()
{
    delete this->meta;
}
