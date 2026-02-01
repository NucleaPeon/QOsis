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


QOsisBook::QOsisBook() :
    OsisCommon()
{
}

void QOsisBook::addChapter(int chapter)
{
    QOsisChapter* chap = new QOsisChapter();
    chap->setChapter(chapter);
    this->_data.insert(chapter, chap);
}

QOsisChapter *QOsisBook::chapter(int chapterNum)
{
    return this->_data.value(chapterNum);
}
QString QOsisBook::name() const
{
    return _name;
}

void QOsisBook::setName(const QString &name)
{
    _name = name;
}

QList<int> QOsisBook::chapters()
{
    return this->_data.keys();
}

int QOsisBook::chapterCount()
{
    return this->_data.keys().count();
}



QOsisStructure::QOsisStructure() :
    OsisCommon()
{
    _order = QList<QString>();
}

QString QOsisStructure::osisIDWork() const
{
    return _osisIDWork;
}

void QOsisStructure::setOsisIDWork(const QString &osisIDWork)
{
    _osisIDWork = osisIDWork;
}
QString QOsisStructure::lang() const
{
    return _lang;
}

void QOsisStructure::setLang(const QString &lang)
{
    _lang = lang;
}
QString QOsisStructure::osisRefWork() const
{
    return _osisRefWork;
}

void QOsisStructure::setOsisRefWork(const QString &osisRefWork)
{
    _osisRefWork = osisRefWork;
}

void QOsisStructure::consumeAttributes(QXmlStreamAttributes attrs)
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
QString QOsisStructure::title() const
{
    return _title;
}

void QOsisStructure::setTitle(const QString &title)
{
    _title = title;
}

void QOsisStructure::addBook(const QString name)
{
    QOsisBook* book = new QOsisBook();
    book->setName(name);
    _order.append(name);
    this->_data.insert(name, book);
}

QOsisBook* QOsisStructure::book(QString name)
{
    return this->_data.value(name);
}

int QOsisStructure::bookCount()
{
    return this->_data.keys().count();
}

QList<QString> QOsisStructure::books() const
{
    return this->_order;
}

int QOsisStructure::chapterCount()
{
    int c = 0;
    QOsisBook* book;
    foreach(QString key, this->_data.keys()) {
        book = this->_data.value(key);
        c += book->chapterCount();
    }
    return c;
}

int QOsisStructure::verseCount()
{
    int c = 0;
    QOsisChapter* chap;
    QOsisBook* book;
    foreach(QString key, this->_data.keys()) {
        book = this->_data.value(key);
        foreach(int chapkey, book->chapters()) {
            chap = book->chapter(chapkey);
            c += chap->verseCount();

        }
    }
    return c;
}

bool QOsisStructure::isEmpty()
{
    return this->_data.isEmpty();
}

QList<QOsisVerse *> QOsisStructure::find(const QString book, const int chapter, const int verse, int additional)
{
    QList<QOsisVerse*> verses;
    if(additional < 0)
        additional = 0;
    QOsisBook* osisbook = this->book(book);
    QOsisChapter* osischap = osisbook->chapter(chapter);
    for(int i = verse; i <= additional; ++i) {
        verses.append(osischap->verse(i));
    }

    return verses;
}

#ifdef QT_DEBUG
const QDebug operator<<(QDebug dbg,  QOsisVerse &verse)
{
    QString name = QString("Verse %1 (%2)").arg(QString(verse.verseNum())).arg(verse.verse());
    return dbg.nospace() << name;
}

const QDebug operator<<(QDebug dbg,  QOsisChapter &chapter)
{
    QString name = QString("%1 (%2 verses)").arg(QString(chapter.chapter()), chapter.verseCount());
    return dbg.nospace() << name;
}

const QDebug operator<<(QDebug dbg,  QOsisBook &book)
{
    QString name = QString("%1 (%2 chapters)").arg(book.name(), book.chapterCount());
    return dbg.nospace() << name;
}

const QDebug operator<<(QDebug dbg,  QOsisStructure &structure)
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


QOsisVerse::QOsisVerse() :
    OsisCommon()
{

}

QString QOsisVerse::verse() const
{
    return _verse;
}

void QOsisVerse::setVerse(const QString &verse)
{
    _verse = verse;
}
int QOsisVerse::verseNum() const
{
    return _versenum;
}

void QOsisVerse::setVerseNum(int versenum)
{
    _versenum = versenum;
}

int QOsisVerse::characterCount()
{
    return this->_verse.count();
}




QOsisChapter::QOsisChapter() :
    OsisCommon()
{

}

void QOsisChapter::addVerse(int verseNum, QString verseText)
{
    QOsisVerse* v = new QOsisVerse();
    v->setVerse(verseText);
    v->setVerseNum(verseNum);
    this->_data.insert(verseNum, v);
}

QOsisVerse* QOsisChapter::verse(int versenum)
{
    return this->_data.value(versenum);
}
int QOsisChapter::chapter() const
{
    return _chapter;
}

void QOsisChapter::setChapter(int chapter)
{
    _chapter = chapter;
}

int QOsisChapter::verseCount()
{
    return this->_data.keys().count();
}

QList<int> QOsisChapter::verses()
{
    return this->_data.keys();
}

