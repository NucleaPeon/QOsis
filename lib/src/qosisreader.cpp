#include "qosisreader.h"
#include <QtCore/QDebug>

using namespace QOSIS;

QOsisReader::QOsisReader() :
    QOsisCommons(""),
    _schema(QOSIS::Globals::XML_NAMESPACE),
    _reader(NULL)
{

}

QOsisReader::QOsisReader(const QString path) :
    QOsisCommons(path),
    _schema(QOSIS::Globals::XML_NAMESPACE),
    _reader(NULL)
{
    this->initReader();
}

QOsisReader::~QOsisReader()
{

}

void QOsisReader::initReader()
{
    // Read when conditions allow
    if (this->isValidPath()) {
        if (_reader == NULL) {
            QFile* f = this->file();
            f->open(QIODevice::ReadOnly);
            QByteArray arr = f->readAll();
            f->close();

            _reader = new QXmlStreamReader(arr);
            _reader->setNamespaceProcessing(false);
            this->parseXml();
        }
    }
}

QXmlStreamReader *QOsisReader::reader()
{
    return _reader;
}

bool QOsisReader::validate()
{
    QOsisValidator v = QOsisValidator(this->path());
    return v.validateXml() == QOSIS::ENUMS::Validation::OK;
}

QOsisStructure *QOsisReader::getOsisData()
{
    return this->_data;
}

void QOsisReader::parseXml()
{
    qDebug() << Q_FUNC_INFO;
    _data = new QOsisStructure();
    _tags = QList<QStringRef>();
    _reader->setNamespaceProcessing(false);
    while(! _reader->atEnd()) {
        _reader->readNext();
        processXml(_reader->name());
    }
}

void QOsisReader::processXml(QStringRef tagname)
{
    if (tagname.isEmpty()) { return; }
    if (_reader->isStartElement()) {
        _tags.append(tagname);
        if (tagname == "osisText") {
            _data->consumeAttributes(_reader->attributes());
        } else if (_tags.contains(HEADER_REF)) {
            if (tagname == "title") {
                _data->setTitle(_reader->readElementText());
            }
        } else if (tagname == "div" && _reader->attributes().contains(QXmlStreamAttribute("type", "book"))) {
            foreach(QXmlStreamAttribute attr, _reader->attributes()) {
                if (attr.name() == "osisID") {
                    const QString bookname = attr.value().toString();
                    _data->addBook(bookname);
                    _data->book(bookname)->setName(bookname);
                }
            }
        } else if (tagname == "chapter" || (tagname == "div" && _reader->attributes().contains(QXmlStreamAttribute("type", "chapter")))) {
            foreach(QXmlStreamAttribute attr, _reader->attributes()) {
                if (attr.name() == "osisID") {
                    QString val = attr.value().toString();
                    QStringList parts = val.split(".");
                    int chapter = parts.at(1).toInt();
                    QOsisBook* book = _data->book(parts.at(0));
                    book->addChapter(chapter);
                }
            }
        } else if (tagname == "verse") {
            foreach(QXmlStreamAttribute attr, _reader->attributes()) {
                if (attr.name() == "osisID") {
                    QString val = attr.value().toString();
                    QStringList parts = val.split(".");
                    int chapter = parts.at(1).toInt();
                    int verse = parts.at(2).toInt();
                    QOsisBook* book = _data->book(parts.at(0));
                    QOsisChapter* chap = book->chapter(chapter);
                    chap->addVerse(verse, _reader->readElementText());
                }
            }
        }
    } else if (_reader->isEndElement()) {
        _tags.pop_back();
    }

}
