#include "qosisexporter.h"
#include <QtCore/QDebug>

using namespace QOSIS;

QOsisExporter::QOsisExporter() :
    QOsisCommons(""),
    _compression(-1)
{

}

QOsisExporter::QOsisExporter(const QString path) :
    QOsisCommons(path),
    _compression(-1)
{

}

QOsisExporter::~QOsisExporter()
{

}

void QOsisExporter::writeJsonFile(QOsisStructure *st)
{
    QJsonObject obj = toJson(st);
    QJsonDocument doc = QJsonDocument(obj);

    QFile file(QString("%1.json").arg(this->path()));
    file.open(QIODevice::ReadWrite);
    if (_compression > 0) {
        QByteArray compressedData = qCompress(doc.toBinaryData(), _compression);
        file.write(compressedData);
    } else {
        file.write(doc.toJson());
    }
    file.close();
}

int QOsisExporter::compressionLevel()
{
    return _compression;
}

void QOsisExporter::setCompressionLevel(int compress)
{
    if (compress >= 0 && compress <= 9)
        this->_compression = compress;
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
