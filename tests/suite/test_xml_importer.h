#ifndef QOSIS_TEST_IMPORTER_H
#define QOSIS_TEST_IMPORTER_H


#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QTest>

#include "qosis.h"

using namespace QOSIS;

class TestXmlImporter : public QObject {

    Q_OBJECT

private slots:
    void testImportJsonFile();
    void testImportJsonCompressedFile();


private:
    QOsis *meta;
};


#endif
