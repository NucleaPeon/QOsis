#include <QtTest/QtTest>
#include <QtCore/QObject>
#include <QtCore/QDebug>

#include "suite/test_xml_meta.h"
//#include "qosis.h"

int main(int argc, char *argv[])
{

    Q_UNUSED(argc)
    Q_UNUSED(argv)
    int result = 0;

    TestXmlMeta *metaTests = new TestXmlMeta();
    result = QTest::qExec(metaTests);

    return result;
}
