#include "analy.h"

analy::analy()
{
    /*
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
QStringList analy::subject(int i,int j){
    QString fileWrite=QString::number(i)+" "+QString::number(j);
    QStringList p={"",""};
    QString str=poems->at(i).content.at(j);
    QList<int> divList;
    divList.append(-1);
    for(int k=0;k<str.length();k++){
        if(isPunc(str[k])){
            divList.append(k);
        }
    }
    if(str.contains("*")){
        for(int ik=0;ik<divList.length()-1;ik++){
            QString temp=str.mid(divList.at(ik)+1,divList.at(ik+1)-divList.at(ik));
            if(temp.contains("*")){
                temp=temp.remove(temp.indexOf("*"),1);
                p[0].append(toSubject(temp));
            }else{
                p[0].append(temp);
            }
            p[1].append(temp);
        }

    }else{
        if(divList.length()-1<=0){
            qDebug() << "Error Length: " << str;
            return p;
        }
        int jk=QRandomGenerator::global()->bounded(divList.length()-1);
        for(int ik=0;ik<divList.length()-1;ik++){
            QString temp=str.mid(divList.at(ik)+1,divList.at(ik+1)-divList.at(ik));
            if(ik==jk){
                p[0].append(toSubject(temp));
            }else{
                p[0].append(temp);
            }
            p[1].append(temp);
        }
        fileWrite.append(" "+QString::number(j));
    }
    fileWrite.append("\n");
    QString titleString;
    titleString.append("——");
    if(poems->at(i).dynasty!=""){
        titleString.append("【"+poems->at(i).dynasty+"】");
    }
    if(poems->at(i).author!=""){
        titleString.append(poems->at(i).author);
    }
    if(poems->at(i).title.contains("《")){
        titleString.append(poems->at(i).title+"\n");
    }else{
        titleString.append("《"+poems->at(i).title+"》\n");
    }
    p[0].append(titleString);
    p[1].append(titleString);
    //QTextStream out(&historyFile);
    //out << fileWrite;
    //out.flush();
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
QStringList analy::generateSelected(QList<bool> *check){
    QStringList p={"",""};
    QList<int> testList;
    while(testList.length()<10){
        int k=QRandomGenerator::global()->bounded(poems->length());
        bool shouldContinue=!check->at(poems->at(k).grade);
        if(shouldContinue) continue;
        for(int i=0;i<testList.length();i++){
            if(testList.at(i)==k){
                shouldContinue=true;
                break;
            }
        }
        if(shouldContinue) continue;
        int j=QRandomGenerator::global()->bounded(poems->at(k).content.length());
        QStringList pp=subject(k,j);
        p[0].append(QString::number(testList.length()+1)+". ");
        p[1].append(QString::number(testList.length()+1)+". ");
        p[0].append(pp.at(0));
        p[1].append(pp.at(1));
        testList.append(k);
        }
    return p;
}
QStringList analy::generateAll(){
   QStringList p={"",""};
   QList<int> testList;
   while(testList.length()<10){
       int k=QRandomGenerator::global()->bounded(poems->length());
       bool shouldContinue=false;
       for(int i=0;i<testList.length();i++){
           if(testList.at(i)==k){
               shouldContinue=true;
               break;
           }
       }
       if(shouldContinue) continue;
       int j=QRandomGenerator::global()->bounded(poems->at(k).content.length());
       QStringList pp=subject(k,j);
       p[0].append(QString::number(testList.length()+1)+". ");
       p[1].append(QString::number(testList.length()+1)+". ");
       p[0].append(pp.at(0));
       p[1].append(pp.at(1));
       testList.append(k);
       }
   return p;
}

void analy::read(QString address){
    QFile file(address);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Can't open the file!"<<endl;
    }
    poem temp;
    int lineNumber=0;
    if(address.contains("7a")){
        temp.grade=0;
    }
    else if(address.contains("7b")){
        temp.grade=1;
    }
    else if(address.contains("8a")){
        temp.grade=2;
    }
    else if(address.contains("8b")){
        temp.grade=3;
    }
    else if(address.contains("9a")){
        temp.grade=4;
    }
    else if(address.contains("9b")){
        temp.grade=5;
    }
    else if(address.contains("mj110q")){
        while(!file.atEnd()){
            QByteArray line = file.readLine();
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            //QString str = QString::fromLocal8Bit(line.data());
            QString str=codec->toUnicode(line);
            str = str.trimmed();
            if(!str.isEmpty()) mjq.append(str);
        }
        return;
    }
    else if(address.contains("mj110a")){
        while(!file.atEnd()){
            QByteArray line = file.readLine();
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            //QString str = QString::fromLocal8Bit(line.data());
            QString str=codec->toUnicode(line);
            str = str.trimmed();
            mja.append(str);
        }
        return;
    }
    else {
        return;
    }
    while(!file.atEnd()){
        QByteArray line = file.readLine();
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        //QString str = QString::fromLocal8Bit(line.data());
        QString str=codec->toUnicode(line);
        str = str.trimmed();
        if(str.isEmpty()){
            if(temp.content.length()>0){
                poems->append(temp);
                temp.content.clear();
                temp.dynasty="";
                temp.author="";
                temp.title="";
                lineNumber=0;
            }else{
                lineNumber=0;
            }
        }else{
            if(lineNumber==0){
                temp.title=str;
                lineNumber++;
            }
            else if(lineNumber==1){
                if(str.contains("【")){
                    int p1=str.indexOf("【");
                    int p2=str.indexOf("】");
                    temp.dynasty=str.mid(p1+1,p2-p1-1);
                    temp.author=str.mid(p2+1);
                }else{
                    bool shouldBreak=false;
                    for(int i=0;i<str.length();i++){
                        if(isPunc(str[i])){
                            temp.content.append(str);
                            shouldBreak=true;
                            break;
                        }
                    }
                    if(!shouldBreak) temp.author=str;
                }
                lineNumber++;
            }
            else{
                temp.content.append(str);
            }
        }
}
}
