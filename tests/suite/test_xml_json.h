#ifndef QOSIS_TEST_JSON_H
#define QOSIS_TEST_JSON_H


#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QTest>

#include <qosis.h>
#include "../variables.h"



using namespace QOSIS;


class TestXmlJSON : public QObject {

    Q_OBJECT

private slots:
    void init();
    void testXmlToJson();
    void cleanup();

private:
    QOsisJson* _json;

};


#endif
