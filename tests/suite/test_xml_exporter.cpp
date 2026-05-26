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
    const QString newpath = QString("%1/%2.json").arg(QDir::tempPath(), "test");
    QOsisExporter::writeJsonFile(newpath, st);

    QFile f(exp->path());
    QVERIFY(f.exists());
}

void TestXmlExporter::testExportToCompressedJsonFile()
{
    QOsisStructure* st = this->meta->reader()->getOsisData();
    QOsisExporter* exp = this->meta->exporter();
    const QString newpath = QString("%1/%2.json").arg(QDir::tempPath(), "test");
    QOsisExporter::writeJsonFile(newpath, st);
    QOsisImporter* imp = this->meta->importer();
    imp->setPath(newpath);
    QOsisStructure* st2 = QOsisImporter::importJsonFile(newpath, -1);
    QVERIFY(st2 != NULL);
    // Compare books and their names for this test. QOsisValidator can have a full compare method.
    QVERIFY(st->books() == st2->books());

    const QString newcpath = QString("%1/%2.jsonc").arg(QDir::tempPath(), "test");
    QOsisExporter::writeJsonFile(newcpath, st, 5);
    QFile compressedfile (newcpath);
    QVERIFY(compressedfile.exists());
    QOsisImporter::importJsonFile(newcpath, 5);
    QOsisStructure* stc = QOsisImporter::importJsonFile(newcpath, 5);
    QVERIFY(st->books() == stc->books());
}
