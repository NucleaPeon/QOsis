#include "test_xml_exporter.h"

void TestXmlExporter::initTestCase()
{
    qDebug() << "initializing test case";
    this->meta = BibleSingleton::getInstance()->meta();
}

void TestXmlExporter::testExportToJsonUsingYYJSON()
{
    QOsisStructure* st = this->meta->reader()->getOsisData();

    // LEFT OFF:
    //
    // Actually writing yyjson code to create a standardized json for osis files.
}
