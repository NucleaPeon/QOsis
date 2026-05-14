#ifndef QOSIS_TEST_WRITER_H
#define QOSIS_TEST_WRITER_H


#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QTest>

#include "qosis.h"
#include "../singletonbook.h"

using namespace QOSIS;

class TestXmlWriter : public QObject {

    Q_OBJECT

private slots:
    void initTestCase();
    void testWriteToJson();

private:
    QOsis *meta;
};


#endif
