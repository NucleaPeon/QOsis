#ifndef QOSISCOMMONS_H
#define QOSISCOMMONS_H

#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtCore/QMap>

#include <QtCore/QXmlStreamAttributes>

#include "qosisglobals.h"

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
    QString _path = NULL;
    QFile* _file;
};


// Classes that represent the xml data we want

class OsisCommon {
public:
    virtual void consumeAttributes(QXmlStreamAttributes attrs) = 0;

};

class OsisVerse {
public:
    OsisVerse(QString verse);

    void consumeAttributes(QXmlStreamAttributes attrs);

private:
    QString _verse;
};

class OsisChapter {
public:
    OsisChapter();

    void consumeAttributes(QXmlStreamAttributes attrs);

    void addVerse(int verseNum, QString verseText);

private:
    QMap<int, OsisVerse> _data;
    int _chapter;
};

class OsisBook {
public:
    OsisBook();

    void consumeAttributes(QXmlStreamAttributes attrs);
    void addChapter(int chapter);
    OsisChapter chapter(int chapterNum);

private:
    QString _name;
    QMap<int, OsisChapter> _data;

};

class OsisStructure : public OsisCommon {
public:
    OsisStructure();

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
    OsisBook book(QString name);

private:
    /*!
     * \brief data is the entirety of Book > Chapter > Verse format that is common for bibles
     * A Book identifier is the name. Chapters are integers (1...N) and verses are as well.
     *
     */
    QHash<QString, OsisBook> _data;

    QString _osisIDWork;
    QString _lang;
    QString _osisRefWork;
    QString _title;
    QString _subject;


};

}


#endif
