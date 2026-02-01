#ifndef TESTS_SINGLETON_BOOK_H
#define TESTS_SINGLETON_BOOK_H

// A singleton that reads and contains an entire bible for use within the testing suite

#include <QObject>
#include <qosis.h>

class BibleSingleton;
class myClass;

class BibleSingleton
{
    friend class myClass;
public:

    static BibleSingleton* getInstance();
    ~BibleSingleton();

    void setOsisStructure(QOsisStructure* osis);
    QOsisStructure* osis();
    void initOsis(QString path);
    QOsis* meta();

private:
    explicit BibleSingleton(QObject *parent = 0);
    QOsisStructure* _ostruct = NULL;
    QOsis *_meta = NULL;

};

class myClass : public BibleSingleton
{
};


#endif
