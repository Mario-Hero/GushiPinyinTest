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
struct poem{
    int grade=0;
    QStringList content;
    QString dynasty;
    QString author;
    QString title;
};


class analy
{
private:
    int p7a=0;
    int p7b=0;
    int p8a=0;
    int p8b=0;
    int p9a=0;
    int p9b=0;
    QList<poem> *poems = new QList<poem>;
    QStringList subject(int i,int j=0);
    static QString toSubject(QString str);
    static bool isPunc(QChar a);
    static QString removeNumber(const QString p);
    //QFile historyFile;
    //bool checkExist(int i,int j,int k=0);
public:
    void read(QString address);
    QStringList generateSelected(QList<bool> *check);
    QStringList generateAll();
    QStringList generatemj();
    QStringList mjq;
    QStringList mja;
    analy();
    ~analy();
};

#endif // ANALY_H
