#ifndef QOSISCOMMONS_H
#define QOSISCOMMONS_H

#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtCore/QMap>

#include <QtCore/QXmlStreamAttributes>

#include "qosisglobals.h"

#ifdef QT_DEBUG
#include <QtCore/QDebug>
#endif

namespace QOSIS {

class QOsisCommons {
public:
    QOsisCommons(const QString path);
    const QString path();
    bool isValidPath();
    void setPath(const QString path);
    QFile* file();

private:
    void processPath();
    QString _path;
    QFile* _file;
};


// Classes that represent the xml data we want

class OsisCommon {
public:
    virtual void consumeAttributes(QXmlStreamAttributes attrs) = 0;

};

class QOsisVerse : public OsisCommon {
public:
    QOsisVerse();

    void consumeAttributes(QXmlStreamAttributes attrs) { Q_UNUSED(attrs) }

    QString verse() const;
    void setVerse(const QString &verse);


    int verseNum() const;
    void setVerseNum(int versenum);

    int characterCount();

#ifdef QT_DEBUG
    const friend QDebug operator<<(QDebug dbg,  QOsisVerse &verse);
#endif


private:
    QString _verse;
    int _versenum;
};

class QOsisChapter : public OsisCommon  {
public:
    QOsisChapter();

    void consumeAttributes(QXmlStreamAttributes attrs) { Q_UNUSED(attrs) }

    void addVerse(int verseNum, QString verseText);
    QOsisVerse* verse(int versenum);

    int chapter() const;
    void setChapter(int chapter);

    int verseCount();
    QList<int> verses();

#ifdef QT_DEBUG
    const friend QDebug operator<<(QDebug dbg,  QOsisChapter &chapter);
#endif


private:
    QMap<int, QOsisVerse*> _data;
    int _chapter;
};

class QOsisBook : public OsisCommon {
public:
    QOsisBook();

    void consumeAttributes(QXmlStreamAttributes attrs) { Q_UNUSED(attrs) }
    void addChapter(int chapter);
    QOsisChapter* chapter(int chapterNum);

    QString name() const;
    void setName(const QString &name);

    QList<int> chapters();

    int chapterCount();
#ifdef QT_DEBUG
    const friend QDebug operator<<(QDebug dbg,  QOsisBook &book);
#endif

private:
    QString _name;
    QMap<int, QOsisChapter*> _data;

};

class QOsisStructure : public OsisCommon {
public:
    QOsisStructure();

    QString osisIDWork() const;
    void setOsisIDWork(const QString &osisIDWork);

    QString lang() const;
    void setLang(const QString &lang);

    QString osisRefWork() const;
    void setOsisRefWork(const QString &osisRefWork);

    void consumeAttributes(QXmlStreamAttributes attrs);
    QString title() const;
    void setTitle(const QString &title);

    void addBook(const QString name);
    QOsisBook *book(QString name);

    int bookCount();

    int chapterCount();

    int verseCount();

    bool isEmpty();

    QList<QOsisVerse*> find(const QString book, const int chapter, const int verse, int additional = 0);
#ifdef QT_DEBUG
    const friend QDebug operator<<(QDebug dbg,  QOsisStructure &structure);
#endif

private:
    /*!
     * \brief data is the entirety of Book > Chapter > Verse format that is common for bibles
     * A Book identifier is the name. Chapters are integers (1...N) and verses are as well.
     *
     */
    QHash<QString, QOsisBook*> _data;

    QString _osisIDWork;
    QString _lang;
    QString _osisRefWork;
    QString _title;
    QString _subject;


};

}


#endif
