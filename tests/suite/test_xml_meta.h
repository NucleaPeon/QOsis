#ifndef QOSIS_TEST_META_H
#define QOSIS_TEST_META_H

#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QTest>
#include <QtCore/QElapsedTimer>

#include "qosis.h"
#include "../singletonbook.h"

using namespace QOSIS;

class TestXmlMeta : public QObject {

    Q_OBJECT

private slots:
    void initTestCase();
    void testGetters();
    void testLoadingOsisFile();
    void testParentage();
    void cleanupTestCase();

private:
    QOsis *meta;
};

#endif
