#include "qosiscommons.h"

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
    OsisChapter* chap = new OsisChapter();
    chap->setChapter(chapter);
    this->_data.insert(chapter, chap);
}

OsisChapter *OsisBook::chapter(int chapterNum)
{
    return this->_data.value(chapterNum);
}
QString OsisBook::name() const
{
    return _name;
}

void OsisBook::setName(const QString &name)
{
    _name = name;
}

QList<int> OsisBook::chapters()
{
    return this->_data.keys();
}

int OsisBook::chapterCount()
{
    return this->_data.keys().count();
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
}
QString OsisStructure::lang() const
{
    return _lang;
}

void OsisStructure::setLang(const QString &lang)
{
    _lang = lang;
}
QString OsisStructure::osisRefWork() const
{
    return _osisRefWork;
}

void OsisStructure::setOsisRefWork(const QString &osisRefWork)
{
    _osisRefWork = osisRefWork;
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
}

void OsisStructure::addBook(const QString name)
{
    OsisBook* book = new OsisBook();
    book->setName(name);
    this->_data.insert(name, book);
}

OsisBook* OsisStructure::book(QString name)
{
    return this->_data.value(name);
}

int OsisStructure::bookCount()
{
    return this->_data.keys().count();
}

int OsisStructure::chapterCount()
{
    int c = 0;
    OsisBook* book;
    foreach(QString key, this->_data.keys()) {
        book = this->_data.value(key);
        c += book->chapterCount();
    }
    return c;
}

int OsisStructure::verseCount()
{
    int c = 0;
    OsisChapter* chap;
    OsisBook* book;
    foreach(QString key, this->_data.keys()) {
        book = this->_data.value(key);
        foreach(int chapkey, book->chapters()) {
            chap = book->chapter(chapkey);
            c += chap->verseCount();

        }
    }
    return c;
}

bool OsisStructure::isEmpty()
{
    return this->_data.isEmpty();
}

QList<OsisVerse *> OsisStructure::find(const QString book, const int chapter, const int verse, int additional)
{
    QList<OsisVerse*> verses;
    if(additional < 0)
        additional = 0;
    OsisBook* osisbook = this->book(book);
    OsisChapter* osischap = osisbook->chapter(chapter);
    for(int i = verse; i <= additional; ++i) {
        verses.append(osischap->verse(i));
    }

    return verses;
}

#ifdef QT_DEBUG
const QDebug operator<<(QDebug dbg,  OsisVerse &verse)
{
    QString name = QString("Verse %1 (%2)").arg(QString(verse.verseNum())).arg(verse.verse());
    return dbg.nospace() << name;
}

const QDebug operator<<(QDebug dbg,  OsisChapter &chapter)
{
    QString name = QString("%1 (%2 verses)").arg(QString(chapter.chapter()), chapter.verseCount());
    return dbg.nospace() << name;
}

const QDebug operator<<(QDebug dbg,  OsisBook &book)
{
    QString name = QString("%1 (%2 chapters)").arg(book.name(), book.chapterCount());
    return dbg.nospace() << name;
}

const QDebug operator<<(QDebug dbg,  OsisStructure &structure)
{
    QString name = QString("%1 (%2) %3").arg(structure.title()).arg(structure.lang());
    if (structure.isEmpty())
        name.arg("(empty)");
    else {
        int books = structure.bookCount();
        int chapters = structure.chapterCount();
        int verses = structure.verseCount();
        QString data = QString("%1 books, %2 chapters, %3 verses").arg(books).arg(chapters).arg(verses);
        name.arg(data);
    }
    return dbg.nospace() << name;
}

#endif


OsisVerse::OsisVerse()
{

}

void OsisVerse::consumeAttributes(QXmlStreamAttributes attrs)
{
    Q_UNUSED(attrs);
    // No attributes used here, so this won't do anything.
}
QString OsisVerse::verse() const
{
    return _verse;
}

void OsisVerse::setVerse(const QString &verse)
{
    _verse = verse;
}
int OsisVerse::verseNum() const
{
    return _versenum;
}

void OsisVerse::setVerseNum(int versenum)
{
    _versenum = versenum;
}

int OsisVerse::characterCount()
{
    return this->_verse.count();
}




OsisChapter::OsisChapter()
{

}

void OsisChapter::consumeAttributes(QXmlStreamAttributes attrs)
{

}

void OsisChapter::addVerse(int verseNum, QString verseText)
{
    OsisVerse* v = new OsisVerse();
    v->setVerse(verseText);
    v->setVerseNum(verseNum);
    this->_data.insert(verseNum, v);
}

OsisVerse* OsisChapter::verse(int versenum)
{
    return this->_data.value(versenum);
}
int OsisChapter::chapter() const
{
    return _chapter;
}

void OsisChapter::setChapter(int chapter)
{
    _chapter = chapter;
}

int OsisChapter::verseCount()
{
    return this->_data.keys().count();
}

QList<int> OsisChapter::verses()
{
    return this->_data.keys();
}

