#ifndef QOSIS_TEST_IMPORTER_H
#define QOSIS_TEST_IMPORTER_H


#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtTest/QTest>

#include <qosis.h>

class TestXmlImporter : public QObject {

    Q_OBJECT

private slots:

private:
    QOsis *meta;
};


#endif
