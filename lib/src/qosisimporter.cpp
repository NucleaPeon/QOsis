#include "qosisimporter.h"
#include <QtCore/QDebug>

using namespace QOSIS;

QOsisImporter::QOsisImporter() :
    QOsisCommons("")
{

}


QOsisImporter::QOsisImporter(const QString path) :
    QOsisCommons(path)
{
}


QOsisImporter::~QOsisImporter()
{

}

QOsisStructure *QOsisImporter::importJsonFile(const QString path, int compression)
{
    QFile file(path);
    QJsonDocument doc;
    if (file.exists())  {
        file.open(QIODevice::ReadOnly);
        QByteArray contents = file.readAll();
        if (compression > 0) {
            QByteArray uncompressedData = qUncompress(contents);
            doc = QJsonDocument::fromJson(uncompressedData);
        } else {
            doc = QJsonDocument::fromJson(contents);
        }
        file.close();
    } else {
        qDebug() << "File does not exist, NULL";
        return NULL;
    }

    return QOsisImporter::processJson(doc);
}

QOsisStructure *QOsisImporter::processJson(QJsonDocument doc)
{
    if (doc.isEmpty()) { return NULL; }
    QOsisStructure *st = new QOsisStructure();
    QJsonObject root = doc.object();
    // Array of books
    const QString title = root.keys().first();
    QJsonArray books = root.value(title).toArray();
    st->setTitle(title);
    QJsonArray chapters;
    QJsonObject bookObj;
    int i = 0,
        j = 0;

    foreach(QJsonValue book, books) {
        bookObj = book.toObject();
        const QString bookTitle = bookObj.keys().first();
        chapters = bookObj.value(bookTitle).toArray();
        QOsisBook* bookAdded = st->addBook(bookTitle);
        // Chapters
        for (i=0; i<chapters.size(); ++i) {
            QOsisChapter* chapAdded = bookAdded->addChapter(i+1);
            const QJsonArray verses = chapters.at(i).toArray();
            // Verses
            for (j=0; j<verses.size(); ++j) {
                chapAdded->addVerse(j, verses.at(j+1).toString());
            }
        }
    }

    return st;

}
