#ifndef QOSIS_TEST_WRITER_H
#define QOSIS_TEST_WRITER_H


#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QTest>

#include <qosis.h>

using namespace QOSIS;

class TestXmlWriter : public QObject {

    Q_OBJECT

private slots:

private:
    QOsis *meta;
};


#endif
