#include "mainwindow.h"
#include <QApplication>
#include"qsplashscreen.h"
#include<qfile.h>

class CommonHelper{
public:
    static void setStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    CommonHelper::setStyle("UIBeauty.qss");//程序外观设置
    QPixmap pix(":/new/prefix1/start.jpg");//启动界面图片
    QSplashScreen *splash=new QSplashScreen();
    splash->showMessage("正在进入 学生兴趣管理系统,资源初始化中...Gakki赛高-》》");
    splash->setPixmap(pix);
    splash->show();

    MainWindow w;

    //w.setWindowIcon(QIcon(":/new/prefix1/IRONMAN.png"));
    w.setWindowTitle("学生兴趣管理系统    --By DFY 0.0");
    a.processEvents();//程序相应鼠标键盘
    splash->finish(&w);//加载启动画面

    QPixmap pi(":/new/prefix1/BGRQ1.png");
    QPalette pa(w.palette());
    pa.setBrush(QPalette::Background,QBrush(pi));

    w.setPalette(pa);//程序界面大小
    w.setAutoFillBackground(false);
    w.resize(1000,600);
    w.setFixedSize(1000,600);
    w.show();
    //rgb 187,212,238

    return a.exec();
}

