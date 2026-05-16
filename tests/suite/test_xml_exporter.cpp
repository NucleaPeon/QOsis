#include "test_xml_exporter.h"

void TestXmlExporter::initTestCase()
{
    qDebug() << "initializing test case";
    this->meta = BibleSingleton::getInstance()->meta();

    const QString path = QDir::tempPath();
    QDir dir = QDir(path);
    dir.mkdir(path);
}

void TestXmlExporter::testExportToJson()
{
    QOsisStructure* st = this->meta->reader()->getOsisData();
    QOsisExporter* exp = this->meta->exporter();
    QJsonObject obj = exp->toJson(st);
    QVERIFY(! obj.isEmpty());
    QJsonDocument doc = QJsonDocument(obj);
    QVERIFY(! doc.isEmpty());
    QVERIFY(doc.isObject());



    // LEFT OFF:
    //
    // yyjson seems to fail to compile on these snow leopard boxes
    // so file github issue with test code and continue on with QJson______


}

void TestXmlExporter::testExportToJsonFile()
{
    QOsisStructure* st = this->meta->reader()->getOsisData();
    QOsisExporter* exp = this->meta->exporter();

    exp->setPath(QDir::tempPath());
    exp->writeJsonFile(st);
    qDebug() << exp->path() << "write path";
}

void TestXmlExporter::testExportToCompressedJsonFile()
{
    QOsisStructure* st = this->meta->reader()->getOsisData();
    QOsisExporter* exp = this->meta->exporter();
    exp->setPath(QDir::tempPath());
    exp->setCompressionLevel(0);
    exp->writeJsonFile(st);
}
