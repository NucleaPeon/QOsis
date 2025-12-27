#include "qosisreader.h"
#include <QtCore/QDebug>

using namespace QOSIS;

QOsisReader::QOsisReader() :
    QOsisCommons("")
{

}

QOsisReader::QOsisReader(const QString path) :
    QOsisCommons(path)
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

void QOsisReader::parseXml()
{
    _data = new OsisStructure();
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
                    _data->addBook(attr.value().toString());
                }
            }
        } else if (tagname == "chapter" || (tagname == "div" && _reader->attributes().contains(QXmlStreamAttribute("type", "chapter")))) {
            foreach(QXmlStreamAttribute attr, _reader->attributes()) {
                if (attr.name() == "osisID") {
                    QString val = attr.value().toString();
                    QStringList parts = val.split(".");
                    _data->book(parts.at(0)).addChapter(parts.at(1).toInt());
                }
            }
        }


//        _tags.append(tagname);
//        QJsonObject data = _root;
//        if (! data.contains(tagname.toString())) {
//            data[tagname.toString()] = QJsonObject();
//            data = data.value(tagname.toString()).toObject();
//        }
//        qDebug() << data;
//        foreach(QStringRef tag, _tags) {
//            if (data.contains(tag.toString())) {
//                QJsonObject o = data.value(tag.toString()).toObject();
//                data = o;
//            } else {
//                QJsonObject o = QJsonObject();
//                data.insert(tag.toString(), o);
//                data = o;
//            }
//        }



//        if (_tags.count() == 1) {
//            // First level tags go into the root node.
//            rootdata.insert(_tags.at(0).toString(), data);
//            qDebug() << "Inserting " << data << "to root data" << rootdata;
//        } else {
//            // Later than first level, go to next to last level and insert last level object there
//            QJsonObject obj = rootdata;
//            for (int i=_tags.count()-1; i >= 1; --i) {
//                QStringRef ref = _tags.at(i);
//                if (! data.contains(ref.toString())) {
//                    obj.insert(ref.toString(), QJsonObject());
//                    obj = data.value(ref.toString()).toObject();
//                }
//                if (i == 1) {
//                    obj.insert(_tags.at(0).toString(), data);
//                }
//            }
//        }
    } else if (_reader->isEndElement()) {
        _tags.pop_back();
    }

}
