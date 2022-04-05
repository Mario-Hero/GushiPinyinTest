#include "mainwindow.h"
#define HEIGHTSCALE 24
#define WIDTHSCALE 38

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QFont font1,font2;
    font1.setPixelSize(height()/HEIGHTSCALE);
    font2.setPixelSize(width()/WIDTHSCALE);
    //font1.setBold(true);
    setWindowTitle("古诗测试");
    choose->setSpacing(0);
    ima.load(":/new/pre/files/logo2.jpg");
    ima=ima.scaledToWidth(width()/6);
    imageLabel->setPixmap(QPixmap::fromImage(ima));
    p7a->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    p7b->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    p8a->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    p8b->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    p9a->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    p9b->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    choose->addWidget(p7a);
    choose->addWidget(p7b);
    choose->addWidget(p8a);
    choose->addWidget(p8b);
    choose->addWidget(p9a);
    choose->addWidget(p9b);
    choose->addWidget(pmj);
    choose->addStretch();
    choose->addWidget(czjName);
    choose->addWidget(imageLabel);
    choose->addWidget(timeLabel);
    buttonLayout->addWidget(generateButton);
    buttonLayout->addWidget(generateAllButton);
    buttonLayout->addWidget(generateAnswer);
    buttonLayout->addWidget(timerStart);
    buttonLayout->addWidget(timerReset);
    //QString startDir="C:\\Users\\Mario\\Documents\\QTProject\\GushiTest\\test";
    //QString startDir=QDir::currentPath();
    QString startDir= ":/new/pre/files";
    qDebug() << startDir;
    QDir dir(startDir);

    foreach(QString dirFile, dir.entryList(QDir::Files)){
        qDebug() << startDir+"\\"+dirFile;
        reader->read(startDir+"\\"+dirFile);
    }
    chooseWidget->setLayout(choose);
    buttonWidget->setLayout(buttonLayout);
    mainWidget->setLayout(mainLayout);
    mainLayout->addWidget(mainText);
    mainLayout->addWidget(buttonWidget);
    this->setMenuWidget(chooseWidget);
    this->setCentralWidget(mainWidget);
    connect(generateButton,SIGNAL(clicked()), this, SLOT(clickGenerate()));
    connect(generateAllButton,SIGNAL(clicked()), this, SLOT(clickGenerateAll()));
    connect(generateAnswer,SIGNAL(clicked()), this, SLOT(clickgenerateAnswer()));
    connect(timerStart,SIGNAL(clicked()), this, SLOT(timerStartEvent()));
    connect(timerReset,SIGNAL(clicked()), this, SLOT(timerResetEvent()));
    connect(pmj,SIGNAL(clicked()), this, SLOT(mjButtonEvent()));
    mainText->setFont(font1);
    timeLabel->setFont(font2);
    czjName->setFont(font2);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
    timeLabel->setText("00:00");
}
void MainWindow::resizeEvent(QResizeEvent *event){
    QFont font1,font2;
    font1.setPixelSize(height()/HEIGHTSCALE);
    font2.setPixelSize(width()/WIDTHSCALE);
    //font1.setBold(true);
    mainText->setFont(font1);
    timeLabel->setFont(font2);
    czjName->setFont(font2);
}


void MainWindow::timerStartEvent(){
    timer->start(1000);
    timeInt=0;
    counting=true;
}
void MainWindow::timerResetEvent(){
     counting=false;
     timeLabel->setText("00:00");
     timeInt=0;
}
void MainWindow::timeOut(){
    if(counting){
        timeInt++;
        QString ss=QString::number(timeInt%60);
        QString mm=QString::number(floor(timeInt/60.0));
        if(timeInt%60<10) ss="0"+ss;
        if(timeInt<600) mm="0"+mm;
        timeLabel->setText(mm+":"+ss);
        timer->start(1000);
    }
}
MainWindow::~MainWindow()
{
}
void MainWindow::mjButtonEvent(){
    timeInt=0;
    timeLabel->setText("00:00");
    counting=false;
    testStringList=reader->generatemj();
    mainText->setText(testStringList.at(0));
    tstate=textState::test;
    generateAnswer->setText("看答案");
}
void MainWindow::clickGenerate(){
    timeInt=0;
    timeLabel->setText("00:00");
    counting=false;
    bool effectiveCheck=false;
    check.clear();
    check.append(p7a->isChecked());effectiveCheck=p7a->isChecked()||effectiveCheck;
    check.append(p7b->isChecked());effectiveCheck=p7b->isChecked()||effectiveCheck;
    check.append(p8a->isChecked());effectiveCheck=p8a->isChecked()||effectiveCheck;
    check.append(p8b->isChecked());effectiveCheck=p8b->isChecked()||effectiveCheck;
    check.append(p9a->isChecked());effectiveCheck=p9a->isChecked()||effectiveCheck;
    check.append(p9b->isChecked());effectiveCheck=p9b->isChecked()||effectiveCheck;
    if(effectiveCheck){
        testStringList=reader->generateSelected(&check);
        mainText->setText(testStringList.at(0));
        tstate=textState::test;
        generateAnswer->setText("看答案");
    }else{
        mainText->setText("");
    }
}
void MainWindow::clickGenerateAll(){
    timeInt=0;
    timeLabel->setText("00:00");
    counting=false;
    testStringList=reader->generateAll();
    mainText->setText(testStringList.at(0));
    tstate=textState::test;
    generateAnswer->setText("看答案");
}
void MainWindow::clickgenerateAnswer(){
    if(testStringList.length()==2){
        if(tstate==textState::test){
            mainText->setText(testStringList.at(1));
            generateAnswer->setText("不看答案");
            tstate=textState::answer;
            counting=false;
        }
        else if(tstate==textState::answer){
            mainText->setText(testStringList.at(0));
            tstate=textState::test;
            generateAnswer->setText("看答案");
        }
    }
}
