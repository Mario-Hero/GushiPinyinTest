#ifndef ANALY_H
#define ANALY_H

#include <QFile>
#include <QString>
#include <QStringList>
#include <QList>
#include <QDebug>
#include <QTextCodec>
#include <QRandomGenerator>
#include <QDir>

struct pinyinChild{
    QString content;
    QString pinyin;
    int8_t testType;

    bool operator == (const pinyinChild b) const{
        return this->content==b.content;
    }
};



struct pinyin{
    QList<pinyinChild> child;
    bool operator == (const pinyin *b) const{
        if(b->child.length()!=this->child.length()) return false;
        for(int i=0;i<child.length();i++){
            if(!(this->child[i] == b->child.at(i))) return false;
        }
        return true;
    }
};


class analy
{
private:

    QStringList subject(int i);
    QStringList subjectError(int i);
    static QString toSubject(QString str);
    static bool isPunc(QChar a);
    static QString removeNumber(const QString p);
    //QFile historyFile;
    //bool checkExist(int i,int j,int k=0);
public:
    QList<pinyin> *pinyins = new QList<pinyin>;
    QList<pinyin> *errors = new QList<pinyin>;
    void read(QString address,bool initialize);
    void rebuild(QString address);
    void random();
    QStringList generateSelected(QList<bool> *check);
    void generateAll();
    void generateError();
    QStringList generatemj();
    QStringList mjq;
    QStringList mja;
    QList<int> testList;
    bool doErrorMode=false;
    bool haveRank=false;
    bool haveError=false;
    int nowStep=0;
    int fullStep=0;
    int fullLength=0;
    void saveError(QString address);
    QString rankSaveName;
    QString errorSaveName;
    analy();
    ~analy();
};

#endif // ANALY_H
