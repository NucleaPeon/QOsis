#ifndef QOSIS_TEST_META_H
#define QOSIS_TEST_META_H

#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QTest>
#include <qosis.h>

class TestXmlMeta : public QObject {

    Q_OBJECT

private slots:
    void initTestCase();
    void testGetters();

    void cleanupTestCase();

private:
    QOsis *meta;
};

#endif
