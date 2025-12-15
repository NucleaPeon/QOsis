#ifndef QOSIS_TEST_VALIDATOR_H
#define QOSIS_TEST_VALIDATOR_H

#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QTest>

#include <qosis.h>

class TestXmlValidator: public QObject {

    Q_OBJECT

private slots:
    void initTestCase();
    void testNothing();
    void cleanupTestCase();

private:
    QOsis *meta;
};


#endif
