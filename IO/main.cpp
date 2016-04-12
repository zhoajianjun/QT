#include <QCoreApplication>
#include <QMap>
#include <QFile>
#include <QDataStream>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QMap<QString,int> map;
    map.insert("red",1);
    map.insert("green",2);
    map.insert("blue",3);

    QFile file("facts.dat");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug()<<"Cannot open file for writing";
        //return;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_6);
    out<<quint32(0X12345678)<<map;

    quint32 n;
    QMap<QString,int> map1;
    QFile file1("facts.dat");
    if(!file1.open(QIODevice::ReadOnly)) {
        qDebug()<<"Cannot read";
        //return;
    }
    QDataStream in(&file1);
    in.setVersion(QDataStream::Qt_5_6);
    in>>n>>map1;
    qDebug()<<n<<endl;
    QMap<QString, int>::const_iterator i = map1.constBegin();
    while (i != map1.constEnd()) {
        qDebug() << i.key() << ": " << i.value() << endl;
        ++i;
    }


    QString fileName="file.txt";

    QString str="CSDN";
    QFile file0(fileName);
    if (!file0.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug()<<"cannot open file";
    }
    QTextStream in1(&file0);
    in1<<str<<"\n";//如果写多行，同上循环即可

    file0.close();

    QString str1;
    QFile file01(fileName);
    if (!file01.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"cannot open file";
    }
    QTextStream out1(&file01);
    str1 = out1.readLine();
    qDebug()<<str1<<endl;
    file01.close();
    return a.exec();
}
