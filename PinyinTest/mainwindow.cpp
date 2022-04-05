#include "mainwindow.h"
#define GONGXI "恭喜你，训练结束"

#define HEIGHTSCALE 24
#define WIDTHSCALE 38

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);
    QFont font1,font2;
    font1.setPixelSize(height()/HEIGHTSCALE);
    font2.setPixelSize(width()/WIDTHSCALE);
    //font1.setBold(true);
    setWindowTitle("拼音测试 正君之教");
    choose->setSpacing(0);
    ima.load(":/new/pre/files/logo2.jpg");
    ima=ima.scaledToWidth(width()/6);
    imageLabel->setPixmap(QPixmap::fromImage(ima));
    choose->addStretch();
    choose->addWidget(doError);
    choose->addWidget(manyTimes);
    //choose->addWidget(czjName);
    choose->addWidget(imageLabel);
    choose->addWidget(timeLabel);
    buttonLayout->addWidget(generateAllButton);
    buttonLayout->addWidget(generateAnswer);
    buttonLayout->addWidget(timerStart);
    buttonLayout->addWidget(timerReset);

    mainLayout->setSpacing(10);
    fullLayout->addLayout(mainLayout);
    fullLayout->addLayout(buttonLayout);
    for(int i=0;i<10;i++){
        QCheckBox *checkbox=new QCheckBox();
        checkbox->setParent(this);
        checkbox->setVisible(true);
        checkbox->setMaximumSize(500,500);
        QLabel *label=new QLabel();
        label->adjustSize();
        label->setParent(this);
        //label->setAlignment(Qt::AlignLeft);
        //label->setText("sdfsdf");
        QHBoxLayout* qhbox=new QHBoxLayout();
        //qhbox->setParent(this);
        checkboxs.append(checkbox);
        testLabels.append(label);
        qhbox->addWidget(checkboxs.at(i));
        qhbox->addWidget(testLabels.at(i));
        qhbox->setStretchFactor(checkboxs.at(i), 1);
        qhbox->setStretchFactor(testLabels.at(i), 10);
        testQHBoxLayouts.append(qhbox); 
        mainLayout->addLayout(testQHBoxLayouts[i],i/2,i%2);
    }

    //QString startDir="C:\\Users\\Mario\\Documents\\QTProject\\GushiTest\\test";
    //QString startDir=QDir::currentPath();
    QString startDir= ":/new/pre/files";
    //qDebug() << startDir;
    QDir dir(startDir);
    QDir nowDir(QCoreApplication::applicationDirPath());
    foreach(QString dirFile, nowDir.entryList(QDir::Files)){
        //qDebug() << QCoreApplication::applicationDirPath()+"\\"+dirFile;
        reader->read(QCoreApplication::applicationDirPath()+"\\"+dirFile,false);
    }
    if(!reader->haveRank){
        foreach(QString dirFile, dir.entryList(QDir::Files)){
            //qDebug() << startDir+"\\"+dirFile;
            reader->read(startDir+"\\"+dirFile,true);
        }
        reader->random();
        reader->rebuild(QCoreApplication::applicationDirPath()+"\\"+reader->rankSaveName);
        reader->nowStep=0;
    }else{
        if(reader->nowStep==reader->fullStep){
            manyTimes->setText(GONGXI);
            generateAllButton->setText("重新开始");
        }else{
            generateAllButton->setText("继续");
        }
    }
    manyTimes->setText("现在已经训练了"+QString::number(reader->nowStep)+"组，还剩"+QString::number(reader->fullStep-reader->nowStep)+"组");
    chooseWidget->setLayout(choose);
    //mainLayout->addWidget(mainText);
    mainWidget->setLayout(fullLayout);
    this->setMenuWidget(chooseWidget);
    this->setCentralWidget(mainWidget);
    connect(generateAllButton,SIGNAL(clicked()), this, SLOT(clickGenerateAll()));
    connect(generateAnswer,SIGNAL(clicked()), this, SLOT(clickgenerateAnswer()));
    connect(timerStart,SIGNAL(clicked()), this, SLOT(timerStartEvent()));
    connect(timerReset,SIGNAL(clicked()), this, SLOT(timerResetEvent()));
    connect(doError,SIGNAL(clicked()), this, SLOT(clickDoError()));
    mainText->setFont(font1);
    timeLabel->setFont(font2);
    czjName->setFont(font2);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
    timeLabel->setText("00:00");
}
void MainWindow::resizeEvent(QResizeEvent *event){
    QFont font1,font2;
    font1.setPixelSize(height()/HEIGHTSCALE);
    font2.setPixelSize(1.2*width()/WIDTHSCALE);
    const int checkboxSize=3/2*height()/HEIGHTSCALE;
    //font1.setBold(true);
    mainText->setFont(font1);
    timeLabel->setFont(font2);
    czjName->setFont(font2);
    manyTimes->setFont(font2);
    for(int i=0;i<10;i++){
        testLabels.at(i)->setFont(font2);
        //checkboxs.at(i)->resize(checkboxSize,checkboxSize);
        checkboxs.at(i)->setStyleSheet("QCheckBox::indicator { width: "+QString::number(checkboxSize)+"px; height: "+QString::number(checkboxSize)+"px;}");
    }
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
    // no use

    timeInt=0;
    timeLabel->setText("00:00");
    counting=false;
    testStringList=reader->generatemj();
    mainText->setText(testStringList.at(0));
    tstate=textState::test;
    generateAnswer->setText("看答案");
    haveClickGenerate=true;
    generateAllButton->setText("下一套题");
}
void MainWindow::clearCheck(){
    for(int i=0;i<10;i++){
        checkboxs.at(i)->setCheckState(Qt::CheckState::Unchecked);
    }
}
void MainWindow::giveCheckBoxState(){
    if(reader->doErrorMode){
        for(int i=0;i<10;i++){
            checkboxs.at(i)->setCheckState(Qt::CheckState::Checked);
        }
    }else{
        for(int i=0;i<10;i++){
            checkboxs.at(i)->setCheckState(Qt::CheckState::Unchecked);
        }
        for(int i=0;i<10;i++){
            if(i>=reader->testList.length() || i+reader->nowStep*10>=reader->pinyins->length()) break;
            for(int j=0;j<reader->errors->length();j++){

               if(reader->errors->at(j)==&reader->pinyins->at(i+reader->nowStep*10)){
                    checkboxs.at(i)->setCheckState(Qt::CheckState::Checked);
                    break;
               }
            }
        }
    }

}
void MainWindow::clickDoError(){ 
    if(reader->errors->length()<=0){
        manyTimes->setText("目前没有错题");
        return;
    }
    manyTimes->setText("随机训练错题。可通过取消勾选错题清除之。");
    generateAllButton->setText("返回");
    if(reader->doErrorMode){
        readCheckBoxError();
    }else{
        readCheckBox();
    }
    reader->doErrorMode=true;
    giveCheckBoxState();
    timeInt=0;
    timeLabel->setText("00:00");
    counting=false;
    reader->generateError();
    for(int i=0;i<10;i++){
        testLabels[i]->setText(reader->mjq[i]);
    }
    tstate=textState::test;
    generateAnswer->setText("看答案");
}
void MainWindow::clickGenerateAll(){
    if(reader->doErrorMode){
        reader->doErrorMode=false;
        readCheckBoxError();
        clearCheck();
        haveClickGenerate=false;
    }
    if(reader->nowStep==reader->fullStep&& reader->fullStep!=0){
        reader->random();
        reader->rebuild(QCoreApplication::applicationDirPath()+"\\"+reader->rankSaveName);
        reader->nowStep=0;
    }
    if(haveClickGenerate){
        readCheckBox();
        clearCheck();
        reader->nowStep++;
    }
    if(reader->nowStep==reader->fullStep&& reader->fullStep!=0){
        manyTimes->setText(GONGXI);
        generateAllButton->setText("重新开始");
    }
    manyTimes->setText("现在已经训练了"+QString::number(reader->nowStep)+"组，还剩"+QString::number(reader->fullStep-reader->nowStep)+"组");
    timeInt=0;
    timeLabel->setText("00:00");
    counting=false;
    reader->generateAll();
    for(int i=0;i<reader->testList.length();i++){
        testLabels[i]->setText(reader->mjq[i]);
    }
    tstate=textState::test;
    generateAnswer->setText("看答案");
    haveClickGenerate=true;
    generateAllButton->setText("下一套题");
    giveCheckBoxState();
    qDebug()<<reader->fullLength;
    qDebug()<<reader->fullStep;
}
void MainWindow::clickgenerateAnswer(){
        if(tstate==textState::test){
            for(int i=0;i<10;i++){
                testLabels[i]->setText(reader->mja[i]);
            }
            generateAnswer->setText("不看答案");
            tstate=textState::answer;
            counting=false;
        }
        else if(tstate==textState::answer){
            for(int i=0;i<10;i++){
                testLabels[i]->setText(reader->mjq[i]);
            }
            tstate=textState::test;
            generateAnswer->setText("看答案");
        }
}
void MainWindow::readCheckBoxError(){
    bool haveChanged=false;
    QList<int> changeList;
    for(int i=0;i<reader->testList.length();i++){
        if(!checkboxs.at(i)->isChecked()){
           //reader->errors->removeAt(reader->testList.at(i));
           changeList.append(reader->testList.at(i));
           haveChanged=true;
        }
    }
    std::sort(changeList.begin(), changeList.end());
    for(int j=changeList.length()-1;j>=0;j--){
       reader->errors->removeAt(changeList.at(j));
    }
    if(haveChanged) reader->saveError(QCoreApplication::applicationDirPath()+"\\"+reader->errorSaveName);
}


void MainWindow::readCheckBox(bool doAdd,bool doClear){
    for(int i=0;i<reader->testList.length();i++){
       if(testLabels[i]->text().isEmpty()) continue;
       if(checkboxs.at(i)->isChecked()&&doAdd){
           bool foundError=false;
           int j=0;
           for(;j<reader->errors->length();j++){
              if(reader->errors->at(j)==&reader->pinyins->at(i+reader->nowStep*10)){
                    //qDebug()<<"found"<<reader->pinyins->at(i+reader->nowStep*10).child.at(0).content;
                    foundError=true;
                    break;
              }
           }
           if(!foundError){
                reader->errors->append(reader->pinyins->at(i+reader->nowStep*10));
           }
       }else{
           if(!doClear) continue;
           bool foundError=false;
           int j=0;
           for(;j<reader->errors->length();j++){
              if(reader->errors->at(j)==&reader->pinyins->at(i+reader->nowStep*10)){
                    //qDebug()<<"found"<<reader->pinyins->at(i+reader->nowStep*10).child.at(0).content;
                    foundError=true;
                    break;
              }
           }
           if(foundError){
                reader->errors->removeAt(j);
           }
       }
    }
    reader->saveError(QCoreApplication::applicationDirPath()+"\\"+reader->errorSaveName);
}

void MainWindow::closeEvent(QCloseEvent *event){
    readCheckBox();
    clearCheck();
    //reader->nowStep++;
    event->accept();
}
