#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextBrowser>
#include "analy.h"
#include <QDebug>
#include <QFont>
#include <QTimer>
#include <QLabel>
#include <QImage>
#include <QCoreApplication>
#include <QCloseEvent>

enum textState{empty,test,answer};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    bool haveClickGenerate=false;
    QWidget *chooseWidget = new QWidget();
    QTextBrowser *mainText = new QTextBrowser();
    QWidget *buttonWidget = new QWidget();
    QWidget *mainWidget = new QWidget();
    QHBoxLayout *choose=new QHBoxLayout();
    QVBoxLayout *fullLayout=new QVBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QGridLayout* mainLayout = new QGridLayout();
    QPushButton *generateAllButton=new QPushButton("生成题目",this);
    QPushButton *generateAnswer=new QPushButton("看答案",this);
    QPushButton *timerStart=new QPushButton("计时开始",this);
    QPushButton *timerReset=new QPushButton("计时重置",this);
    QPushButton *doError=new QPushButton("复习错题",this);
    QList<QCheckBox*> checkboxs;
    QList<QLabel*> testLabels;
    QList<QHBoxLayout*> testQHBoxLayouts;
    QLabel *czjName=new QLabel("正君之教");
    QLabel *manyTimes=new QLabel("做题数量");
    analy *reader = new analy();
    QStringList testStringList;
    textState tstate=textState::empty;
    QTimer *timer = new QTimer(this);
    QLabel *timeLabel= new QLabel(this);
    void clearCheck();
    bool counting=false;
    int timeInt=0;
    QImage ima;
    QLabel *imageLabel= new QLabel;
    void giveCheckBoxState();
public:
    QList<bool> check;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
    void readCheckBox(bool doAdd=true,bool doClear=true);
    void readCheckBoxError();

public slots:
    void clickGenerateAll();
    void clickgenerateAnswer();
    void timeOut();
    void timerStartEvent();
    void timerResetEvent();
    void mjButtonEvent();
    void clickDoError();
};
#endif // MAINWINDOW_H
