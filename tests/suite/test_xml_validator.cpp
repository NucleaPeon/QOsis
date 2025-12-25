#include "test_xml_validator.h"


void TestXmlValidator::initTestCase()
{

}

void TestXmlValidator::testOnlineSchemaValidation()
{
    QUrl url(XML_NAMESPACE);
    QXmlSchema schema;

    QFile* f = new QFile("://");
    f->open(QIODevice::ReadOnly);
    QByteArray arr = f->readAll();
    f->close();

    schema.load(arr);
    QVERIFY(schema.isValid());

}

void TestXmlValidator::testSchemaValidation()
{

//    QUrl schemaUrl("file:///home/user/schema.xsd");

//    QXmlSchema schema;
//    schema.load(schemaUrl);

//    if (schema.isValid()) {
//        QFile file("test.xml");
//        file.open(QIODevice::ReadOnly);

//        QXmlSchemaValidator validator(schema);
//        if (validator.validate(&file, QUrl::fromLocalFile(file.fileName())))
//            qDebug() << "instance document is valid";
//        else
//            qDebug() << "instance document is invalid";
//    }
}

void TestXmlValidator::cleanupTestCase()
{

}
