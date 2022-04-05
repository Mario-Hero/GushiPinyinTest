#include "analy.h"


analy::analy()
{
    rankSaveName="pinyinRank.txt";
    errorSaveName="pinyinError.txt";
    /*
     *
    historyFile.setFileName("C:\\Users\\Mario\\Documents\\QTProject\\GushiTest\\test\\history.zelda");
    if(!historyFile.open(QIODevice::ReadWrite  | QIODevice::Text)){
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!historyFile.atEnd()){
        QByteArray line = historyFile.readLine();
        QString str(line);
        //qDebug() << str;
    }
    */
}

/*
bool analy::checkExist(int i,int j,int k){
    return false;
}
*/
bool analy::isPunc(QChar a){
    return a==','||a=='.'||a=='?'||a=='!'||a=="？"||a=="，"||a=="。"||a=="！"||a=="；"||a==";";
}
QString analy::toSubject(QString str){
    QString p="";
    for(int k=0;k<str.length();k++){
        if(isPunc(str[k])){
            p.append(str[k]);
        }else{
            p.append("__");
        }
    }
    return p;
}
QStringList analy::subjectError(int i){
    QStringList p={"",""};
    QString test;
    QString ans;
    if(i>=errors->length()||i<0) return p;
    for(int j=0;j<errors->at(i).child.length();j++){
        if(errors->at(i).child[j].testType==3){   //给拼音写汉字
            if(errors->at(i).child[j].pinyin.isEmpty()){
                test.append(errors->at(i).child[j].content);
                ans.append(errors->at(i).child[j].content);
            }else{
                ans.append(errors->at(i).child[j].content);
                test.append("__");
                ans.append("("+errors->at(i).child[j].pinyin+")");
                test.append("("+errors->at(i).child[j].pinyin+")");
            }

        }
        else if(errors->at(i).child[j].testType==1){//给汉字写拼音
            ans.append(errors->at(i).child[j].content);
            test.append(errors->at(i).child[j].content);
            test.append("(___)");
            ans.append("("+errors->at(i).child[j].pinyin+")");
        }
        else if(errors->at(i).child[j].testType==2){
            if(errors->at(i).child[j].pinyin.isEmpty()){
                test.append(errors->at(i).child[j].content);
                ans.append(errors->at(i).child[j].content);
            }
            else if(QRandomGenerator::global()->bounded(2)==0){
                ans.append(errors->at(i).child[j].content);
                test.append("__");
                ans.append("("+errors->at(i).child[j].pinyin+")");
                test.append("("+errors->at(i).child[j].pinyin+")");
            }else{
                ans.append(errors->at(i).child[j].content);
                test.append(errors->at(i).child[j].content);
                test.append("(___)");
                ans.append("("+errors->at(i).child[j].pinyin+")");
            }
        }
        else if(errors->at(i).child[j].testType==0){
            test.append(errors->at(i).child[j].content);
            ans.append(errors->at(i).child[j].content);
            if(!errors->at(i).child[j].pinyin.isEmpty()){
                test.append("("+errors->at(i).child[j].pinyin+")");
                ans.append("("+errors->at(i).child[j].pinyin+")");
            }

        }
    }
    p[0]=test;
    p[1]=ans;
    return p;
}


QStringList analy::subject(int i){
    QStringList p={"",""};
    QString test;
    QString ans;
    if(i>=pinyins->length()||i<0) return p;
    for(int j=0;j<pinyins->at(i).child.length();j++){
        if(pinyins->at(i).child[j].testType==3){   //给拼音写汉字
            if(pinyins->at(i).child[j].pinyin.isEmpty()){
                test.append(pinyins->at(i).child[j].content);
                ans.append(pinyins->at(i).child[j].content);
            }else{
                ans.append(pinyins->at(i).child[j].content);
                test.append("__");
                ans.append("("+pinyins->at(i).child[j].pinyin+")");
                test.append("("+pinyins->at(i).child[j].pinyin+")");
            }

        }
        else if(pinyins->at(i).child[j].testType==1){//给汉字写拼音
            ans.append(pinyins->at(i).child[j].content);
            test.append(pinyins->at(i).child[j].content);
            test.append("(___)");
            ans.append("("+pinyins->at(i).child[j].pinyin+")");
        }
        else if(pinyins->at(i).child[j].testType==2){
            if(pinyins->at(i).child[j].pinyin.isEmpty()){
                test.append(pinyins->at(i).child[j].content);
                ans.append(pinyins->at(i).child[j].content);
            }
            else if(QRandomGenerator::global()->bounded(2)==0){
                ans.append(pinyins->at(i).child[j].content);
                test.append("__");
                ans.append("("+pinyins->at(i).child[j].pinyin+")");
                test.append("("+pinyins->at(i).child[j].pinyin+")");
            }else{
                ans.append(pinyins->at(i).child[j].content);
                test.append(pinyins->at(i).child[j].content);
                test.append("(___)");
                ans.append("("+pinyins->at(i).child[j].pinyin+")");
            }
        }
        else if(pinyins->at(i).child[j].testType==0){
            test.append(pinyins->at(i).child[j].content);
            ans.append(pinyins->at(i).child[j].content);
            if(!pinyins->at(i).child[j].pinyin.isEmpty()){
                test.append("("+pinyins->at(i).child[j].pinyin+")");
                ans.append("("+pinyins->at(i).child[j].pinyin+")");
            }

        }
    }
    p[0]=test;
    p[1]=ans;
    return p;
}

QString analy::removeNumber(const QString p){
    return p.mid(p.indexOf(".")+1);
}
QStringList analy::generatemj(){
    QStringList p={"",""};
    QList<int> testList;
     while(testList.length()<10){
          int k=QRandomGenerator::global()->bounded(mjq.length());
          int testK=mjq.at(k).left(mjq.at(k).indexOf(".")).toInt();
          bool shouldContinue=false;
          for(int i=0;i<testList.length();i++){
              if(testList.at(i)==testK){
                  shouldContinue=true;
                  break;
              }
          }
          if(shouldContinue) continue;
          testList.append(testK);
          p[0].append(QString::number(testList.length())+". "+removeNumber(mjq.at(k))+"\n");
          p[1].append(QString::number(testList.length())+". "+removeNumber(mja.at(testK-1))+"\n");
     }
     return p;
}
void analy::generateError(){
    testList.clear();
    mjq.clear();
    mja.clear();
    if(errors->length()>=10){
    while (testList.length()<10) {
        int k=QRandomGenerator::global()->bounded(errors->length());
        bool shouldContinue=false;
        for(int i=0;i<testList.length();i++){
            if(testList.at(i)==k){
                shouldContinue=true;
                break;
            }
        }
        if(shouldContinue) continue;
         QStringList pp=subjectError(k);
         mjq.append(pp.at(0));
         mja.append(pp.at(1));
         testList.append(k);
    }
    }else{
        int k=0;
        for(;k<errors->length();k++){
            QStringList pp=subjectError(k);
            mjq.append(pp.at(0));
            mja.append(pp.at(1));
            testList.append(k);
        }
        for(int i=0;i<10-k;i++){
            mjq.append("");
            mja.append("");
        }
    }
}
void analy::generateAll(){
   testList.clear();
   mjq.clear();
   mja.clear();
   for(int k=0;k<10;k++){
       if(nowStep*10+k>pinyins->length()){
           mjq.append("");
           mja.append("");
           continue;
       }
       QStringList pp=subject(k+nowStep*10);
       mjq.append(pp.at(0));
       mja.append(pp.at(1));
       testList.append(k+nowStep*10);
   }
}

void analy::random(){
    for(int i=0;i<pinyins->length();i++){
        int k=QRandomGenerator::global()->bounded(pinyins->length());
        pinyins->swapItemsAt(i,k);
    }
}

void analy::saveError(QString address){
    QFile file(address);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"Can't open the file!"<<Qt::endl;
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    in<<nowStep<<Qt::endl;
    for(int i=0;i<errors->length();i++){
       for(int j=0;j<errors->at(i).child.length();j++){
           in<<errors->at(i).child[j].content;
           if(!errors->at(i).child[j].pinyin.isEmpty()){
               in<<"("<<errors->at(i).child[j].pinyin<<")";
           }
           if(errors->at(i).child[j].testType!=3){
              in<<QString::number(errors->at(i).child[j].testType);
           }
       }
       in<<Qt::endl;
    }
    in.flush();
    file.close();

}

void analy::rebuild(QString address){
    QFile file(address);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"Can't open the file!"<<Qt::endl;
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    for(int i=0;i<pinyins->length();i++){
       for(int j=0;j<pinyins->at(i).child.length();j++){
           in<<pinyins->at(i).child[j].content;
           if(!pinyins->at(i).child[j].pinyin.isEmpty()){
               in<<"("<<pinyins->at(i).child[j].pinyin<<")";
           }
           if(pinyins->at(i).child[j].testType!=3){
              in<<QString::number(pinyins->at(i).child[j].testType);
           }
       }
       in<<Qt::endl;
    }
    in.flush();
    file.close();
}

void analy::read(QString address, bool initialize=true){
    QFile file(address);
    int thisTimeWeReadWhat=0; //0 nothing 1 rank 2 error
    if(!file.fileName().contains(".txt")) return;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Can't open the file" << file.fileName()<<Qt::endl;
    }
    qDebug()<<file.fileName();
    if(file.fileName().contains(rankSaveName)){
        haveRank=true;
        thisTimeWeReadWhat=1;
        qDebug()<<"Find Rank!";
    }
    else if(file.fileName().contains(errorSaveName)){
        haveError=true;
        thisTimeWeReadWhat=2;
    }else if(haveRank){
        return;
    }else if(initialize&&file.fileName().contains("pinyin.txt")){
        haveRank=true;
        thisTimeWeReadWhat=1;
        qDebug()<<"Find Original!";
    }
    int lineNumber=0;
    while(!file.atEnd()){
        pinyin pinyint;
        QByteArray line = file.readLine();
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        //QString str = QString::fromLocal8Bit(line.data());
        QString str=codec->toUnicode(line);
        str = str.trimmed();
        if(str.isEmpty()||(str.length()<2&&!str.at(0).isNumber())){
            continue;
        }else{
            if(lineNumber==0 && thisTimeWeReadWhat==2){
                if(str.at(0).isNumber()){
                    nowStep=str.toInt();
                    qDebug()<<"NowStep: "<<nowStep;
                    continue;
                }
            }
            lineNumber++;
            int lasti=0;
            pinyinChild temp;
            temp.testType=3;
            for(int i=0;i<str.length();i++){
                QChar cha = str.at(i);
                if(cha.isNumber()){
                    if(cha=='0'){
                       temp.testType=0;
                    }else if(cha=='1'){
                       temp.testType=1;
                    }else if(cha=='2'){
                       temp.testType=2;
                    }else{
                        qDebug()<<"Error.Wrong number."<<cha;
                    }
                }else{
                    ushort uni = cha.unicode();
                    if(uni >= 0x4E00 && uni <= 0x9FA5){
                        if(i==0){
                            temp.content=cha;
                            temp.pinyin.clear();
                            temp.testType=3;
                        }else{
                            pinyint.child.append(temp);
                            temp.content=cha;
                            temp.pinyin.clear();
                            temp.testType=3;
                        }
                    }
                    else if(str[i]=='('){
                        lasti=i+1;
                    }
                    else if(str[i]==')'){
                        temp.pinyin=str.mid(lasti,i-lasti);
                    }
                }
            }
            pinyint.child.append(temp);
            if(thisTimeWeReadWhat==1){
               pinyins->append(pinyint);
            }else{
               errors->append(pinyint);
            }

        }    
    }
    if(lineNumber<=40 && thisTimeWeReadWhat==1){
       haveRank=false;
       return;
    }
    if(thisTimeWeReadWhat==1){
        fullLength=lineNumber;
        fullStep=ceil(fullLength/10.0);
    }

}
