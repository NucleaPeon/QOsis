#ifndef QOSIS_TEST_READER_H
#define QOSIS_TEST_READER_H


#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QTest>

#include <qosis.h>

using namespace QOSIS;

static const QString TEST_FILE = "://kjv.xml";

class TestXmlReader : public QObject {

    Q_OBJECT
public:

private slots:
    void initTestCase();
    void testConstructors();
    void testReadingFile();
    void cleanupTestCase();

private:
    QOsis *meta;
};


#endif
