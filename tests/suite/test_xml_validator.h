#ifndef QOSIS_TEST_VALIDATOR_H
#define QOSIS_TEST_VALIDATOR_H

#include <QtCore/QCoreApplication>
#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QTest>
#include <QtCore/QUrl>
#include <QtCore/QBuffer>
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QtXmlPatterns/QXmlSchema>
#endif

#include "qosis.h"
#include "../singletonbook.h"

using namespace QOSIS;
using namespace QOSIS::Globals;

class TestXmlValidator: public QObject {

    Q_OBJECT

private slots:
    void initTestCase();
    void testSchemaValidation();
    void cleanupTestCase();

private:
    QOsis *meta;
    QCoreApplication *app;
};


#endif
