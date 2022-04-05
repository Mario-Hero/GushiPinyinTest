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
enum textState{empty,test,answer};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *chooseWidget = new QWidget();
    QTextBrowser *mainText = new QTextBrowser();
    QWidget *buttonWidget = new QWidget();
    QWidget *mainWidget = new QWidget();
    QHBoxLayout *choose=new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QCheckBox *p9b=new QCheckBox("九下",chooseWidget);
    QCheckBox *p9a=new QCheckBox("九上",chooseWidget);
    QCheckBox *p8b=new QCheckBox("八下",chooseWidget);
    QCheckBox *p8a=new QCheckBox("八上",chooseWidget);
    QCheckBox *p7b=new QCheckBox("七下",chooseWidget);
    QCheckBox *p7a=new QCheckBox("七上",chooseWidget);
    QPushButton *pmj=new QPushButton("名句",chooseWidget);
    QPushButton *generateButton=new QPushButton("生成所选题目",this);
    QPushButton *generateAllButton=new QPushButton("生成全部题目",this);
    QPushButton *generateAnswer=new QPushButton("看答案",this);
    QPushButton *timerStart=new QPushButton("计时开始",this);
    QPushButton *timerReset=new QPushButton("计时重置",this);
    QLabel *czjName=new QLabel("正君之教");
    analy *reader = new analy();
    QStringList testStringList;
    textState tstate=textState::empty;
    QTimer *timer = new QTimer(this);
    QLabel *timeLabel= new QLabel(this);
    bool counting=false;
    int timeInt=0;
    QImage ima;
    QLabel *imageLabel= new QLabel;
public:
    QList<bool> check;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    virtual void resizeEvent(QResizeEvent *event) override;

public slots:
    void clickGenerate();
    void clickGenerateAll();
    void clickgenerateAnswer();
    void timeOut();
    void timerStartEvent();
    void timerResetEvent();
    void mjButtonEvent();
};
#endif // MAINWINDOW_H
