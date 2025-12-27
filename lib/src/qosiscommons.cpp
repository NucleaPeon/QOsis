#include "qosiscommons.h"
#include <QtCore/QDebug>

using namespace QOSIS;

QOsisCommons::QOsisCommons(const QString path)
{
    this->setPath(path);
}

const QString QOsisCommons::path()
{
    return this->_path;
}

bool QOsisCommons::isValidPath()
{
    return ! this->_path.isEmpty() && QFile(this->_path).exists();
}

void QOsisCommons::setPath(const QString path)
{
    this->_path = path;
    this->processPath();
}

QFile *QOsisCommons::file()
{
    return this->_file;
}

void QOsisCommons::processPath()
{
    if (isValidPath()) {
        _file = new QFile(this->_path);
    }

}


OsisBook::OsisBook()
{
}

void OsisBook::consumeAttributes(QXmlStreamAttributes attrs)
{

}

void OsisBook::addChapter(int chapter)
{
    this->_data.insert(chapter, OsisChapter());
    qDebug() << "Adding chapter" << chapter;
}

OsisChapter OsisBook::chapter(int chapterNum)
{
    return this->_data.value(chapterNum);
}


OsisStructure::OsisStructure()
{

}

QString OsisStructure::osisIDWork() const
{
    return _osisIDWork;
}

void OsisStructure::setOsisIDWork(const QString &osisIDWork)
{
    _osisIDWork = osisIDWork;
    qDebug() << _osisIDWork;
}
QString OsisStructure::lang() const
{
    return _lang;
}

void OsisStructure::setLang(const QString &lang)
{
    _lang = lang;
    qDebug() << _lang;
}
QString OsisStructure::osisRefWork() const
{
    return _osisRefWork;
}

void OsisStructure::setOsisRefWork(const QString &osisRefWork)
{
    _osisRefWork = osisRefWork;
    qDebug() << _osisRefWork;
}

void OsisStructure::consumeAttributes(QXmlStreamAttributes attrs)
{
    foreach(QXmlStreamAttribute attr, attrs) {
        if (attr.name() == "lang")
            this->setLang(attr.value().toString());
        else if (attr.name() == "osisIDWork")
            this->setOsisIDWork(attr.value().toString());
        else if (attr.name() == "osisRefWork")
            this->setOsisRefWork(attr.value().toString());
    }
}
QString OsisStructure::title() const
{
    return _title;
}

void OsisStructure::setTitle(const QString &title)
{
    _title = title;
    qDebug() << _title;
}

void OsisStructure::addBook(const QString name)
{
    this->_data.insert(name, OsisBook());
}

OsisBook OsisStructure::book(QString name)
{
    return this->_data.value(name);
}


OsisVerse::OsisVerse(QString verse) :
    _verse(verse)
{

}

void OsisVerse::consumeAttributes(QXmlStreamAttributes attrs)
{
    Q_UNUSED(attrs);
    // No attributes used here, so this won't do anything.
}


OsisChapter::OsisChapter()
{

}

void OsisChapter::consumeAttributes(QXmlStreamAttributes attrs)
{

}

void OsisChapter::addVerse(int verseNum, QString verseText)
{
    this->_data.insert(verseNum, OsisVerse(verseText));
}
