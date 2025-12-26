#include <QtTest/QtTest>
#include <QtCore/QObject>
#include <QtCore/QDebug>

#include "suite/test_xml_meta.h"
#include "suite/test_xml_validator.h"
#include "suite/test_xml_reader.h"
#include "suite/test_xml_writer.h"
#include "suite/test_xml_importer.h"
#include "suite/test_xml_exporter.h"

//#include "qosis.h"

int main(int argc, char *argv[])
{

    Q_UNUSED(argc)
    Q_UNUSED(argv)
    int result = 0;

    TestXmlMeta *metaTests = new TestXmlMeta();
    result = QTest::qExec(metaTests);

    TestXmlValidator *validateTests = new TestXmlValidator();
//    result = QTest::qExec(validateTests);

    TestXmlReader *readerTests = new TestXmlReader();
    result = QTest::qExec(readerTests);

    TestXmlWriter *writerTests = new TestXmlWriter();
    result = QTest::qExec(writerTests);

    TestXmlImporter *importTests = new TestXmlImporter();
    result = QTest::qExec(importTests);

    TestXmlExporter *exportTests = new TestXmlExporter();
    result = QTest::qExec(exportTests);

    return result;
}
