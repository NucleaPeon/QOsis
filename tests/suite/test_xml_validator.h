#ifndef QOSIS_TEST_VALIDATOR_H
#define QOSIS_TEST_VALIDATOR_H

#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QTest>
#include <QtCore/QUrl>

#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtXmlPatterns/QXmlSchema>

#include <qosis.h>

using namespace QOSIS;
using namespace QOSIS::Globals;

class TestXmlValidator: public QObject {

    Q_OBJECT

private slots:
    void initTestCase();
    void testOnlineSchemaValidation();
    void testSchemaValidation();
    void cleanupTestCase();

private:
    QOsis *meta;
};


#endif
