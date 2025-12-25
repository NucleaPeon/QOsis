#include "test_xml_validator.h"


void TestXmlValidator::initTestCase()
{
    int argc = 0;
    char* argv = "";
    char** argvpp = &argv;
    app = new QCoreApplication(argc, argvpp);
}

void TestXmlValidator::testSchemaValidation()
{
    QXmlSchema schema;
    QFile* f = new QFile("://osisCore.2.1.1.xsd");
    f->open(QIODevice::ReadOnly);
    QByteArray xsd = f->readAll();
    f->close();
    schema.load(xsd);
    QVERIFY(schema.isValid());

    QFile* file = new QFile("://kjv.xml");
    file->open(QIODevice::ReadOnly);
    QByteArray data = file->readAll();
    file->close();

    QBuffer buffer(&data);
    buffer.open(QIODevice::ReadOnly);

    QXmlSchemaValidator validator(schema);
    QVERIFY(validator.validate(&buffer));
}

void TestXmlValidator::cleanupTestCase()
{
    delete app;
}
