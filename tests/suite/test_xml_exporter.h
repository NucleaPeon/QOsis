#ifndef QOSIS_TEST_EXPORTER_H
#define QOSIS_TEST_EXPORTER_H


#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QTest>

#include "qosis.h"

#include "../singletonbook.h"

using namespace QOSIS;

class TestXmlExporter : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void testExportToJsonUsingYYJSON();
private:
    QOsis *meta;
};


#endif
