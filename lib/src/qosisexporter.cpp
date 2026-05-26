#include "qosisexporter.h"
#include <QtCore/QDebug>

using namespace QOSIS;

QOsisExporter::QOsisExporter() :
    QOsisCommons("")
{

}

QOsisExporter::QOsisExporter(const QString path) :
    QOsisCommons(path)
{

}

QOsisExporter::~QOsisExporter()
{

}

void QOsisExporter::writeJsonFile(const QString path, QOsisStructure *st, int compression)
{
    QJsonObject obj = QOsisExporter::toJson(st);
    QJsonDocument doc = QJsonDocument(obj);

    QFile file(path);
    file.open(QIODevice::ReadWrite);
    if (compression > 0) {
        QByteArray compressedData = qCompress(doc.toJson(), compression);
        file.write(compressedData);
    } else {
        file.write(doc.toJson());
    }
    file.close();
}

QJsonObject QOsisExporter::toJson(QOsisStructure *st)
{
    QJsonObject obj;
    QJsonArray barr = QJsonArray();
    for(int i = 0; i < st->bookCount(); ++i) {
        QOsisBook* book = st->book(st->books().at(i));
        QJsonArray carr;
        foreach(int chap, book->chapters()) {
            QOsisChapter* chapter = book->chapter(chap);
            QJsonArray varr;
            foreach(int verse, chapter->verses()) {
                varr.append(chapter->verse(verse)->verse());
            }
            carr.append(varr);
        }
        QJsonObject bookObj = QJsonObject();
        bookObj.insert(book->name(), carr);
        barr.append(bookObj);
    }
    obj.insert(st->title(), barr);
    return obj;
}
