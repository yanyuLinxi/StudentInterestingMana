#include "mainwindow.h"
#include "ui_mainwindow.h"


#include"qnetwork.h"
#include"qdebug.h"
#include"qhostinfo.h"
#include"qhostaddress.h"
#include"qprocess.h"
#include"qnetworkinterface.h"
#include"qdesktopservices.h"
#include"qdatetime.h"

#include"fstream"
#include"sstream"

#include"qmessagebox.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isSave=true;

    QObject::connect(ui->addNewStudentAction,SIGNAL(triggered(bool)),this,SLOT(addNewStudentSlot()));
    QObject::connect(ui->showAllInfoActon,SIGNAL(triggered(bool)),this,SLOT(showAllInfo()));
    QObject::connect(ui->showAllInfoBySearchDeAction,SIGNAL(triggered(bool)),this,SLOT(showAllInfoBySearchDe()));
    QObject::connect(ui->showAllInfoBySearchIdAction,SIGNAL(triggered(bool)),this,SLOT(showAllInfoBySearchId()));
    QObject::connect(ui->showAllInfoBySearchNameAction,SIGNAL(triggered(bool)),this,SLOT(showAllInfoBySearchName()));

    _s.getDataFromFile();
    _i.getDataFromFile();

    QObject::connect(ui->showInteAction,SIGNAL(triggered(bool)),this,SLOT(showInteSlot()));
    QObject::connect(ui->addInteAction,SIGNAL(triggered(bool)),this,SLOT(addInteSlot()));
    QObject::connect(ui->useInfoAction,SIGNAL(triggered(bool)),this,SLOT(useInfoSlot()));
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    showInfo="登录机器:"+getMachineName()+"\n登录用户"+getUserName()+"\n登录时间"+current_date;
    ifstream ifs("StudentsInterestingMana-InfoData.txt");
    string temp;
    char str[100];
    while(ifs.getline(str,100))
    {
        istringstream _is(str);
        string a;
        _is>>a;
        a+="\n";
        temp+=a;
    }
    lastInfo=QString::fromStdString(temp);

    ui->infoLabel->setWordWrap(true);
    QString stuNumber="已注册学生总人数:"+QString::number(_s.stu.size())+"人。";
    ui->textBrowser->setText(showInfo+"\n\n"+lastInfo+"\n\n"+stuNumber);
}

void MainWindow::useInfoSlot()
{
    QMessageBox::information(this,QString::fromUtf8("帮助"),QString::fromUtf8("作者认为软件操作简单，所以没有帮助说明。。。"));
}

MainWindow::~MainWindow()
{
    if(isSave){
        this->_s.setData2File();
        this->_i.setData2File();
    }

    ofstream ofs("StudentsInterestingMana-InfoData.txt");
    lastInfo="上一次登录:\n"+showInfo;
    ofs<<lastInfo.toStdString();
    ofs.close();



    delete ui;
}

void MainWindow::addInteSlot()
{
    pAddInte=new addInteDialog();
    pAddInte->setWindowTitle("添加兴趣");
    pAddInte->setData(_i);
    pAddInte->showInte();
    pAddInte->exec();
    _i=pAddInte->_i;
    delete pAddInte;
}

void MainWindow::setData(studentMana &_s, inteClassMana &_i)
{
    this->_s=_s;
    this->_i=_i;
}

void MainWindow::set_i(inteClassMana &_i)
{
    this->_i=_i;
}

void MainWindow::set_s(studentMana &_s)
{
    this->_s=_s;
}

void MainWindow::showInteSlot()
{
    pShowInte=new showInteDialog();
    pShowInte->setWindowTitle("展示所有兴趣");
    pShowInte->setData(_s,_i);
    pShowInte->showInte();
    pShowInte->exec();
    this->_i=pShowInte->_i;
    this->_s=pShowInte->_s;

    delete pShowInte;
}



void MainWindow::addNewStudentSlot()
{
    pAddStu=new addStudentDialog();
    pAddStu->setData(_s);
    pAddStu->isAdd=true;
    pAddStu->setWindowTitle("添加新学生信息");
    pAddStu->exec();
    this->_s=pAddStu->_s;


    delete pAddStu;
}

void MainWindow::showAllInfo()
{
    pShowAllInfo=new showAllInfoDialog();

    pShowAllInfo->setWindowTitle("展示所有信息");
    pShowAllInfo->setData(_s,_i);
    pShowAllInfo->exec();
    this->_s=pShowAllInfo->_s;
    this->_i=pShowAllInfo->_i;

    delete pShowAllInfo;
    pShowAllInfo=nullptr;
}

void MainWindow::on_pushButton_clicked()
{
    //do nothing;
}


void MainWindow::showAllInfoBySearchDe()
{
    pShowAllInfo=new showAllInfoDialog();

    pShowAllInfo->setWindowTitle("展示所有信息");
    pShowAllInfo->setData(_s,_i);
    pShowAllInfo->setTabInde(2);
    pShowAllInfo->exec();
    this->_s=pShowAllInfo->_s;
    this->_i=pShowAllInfo->_i;
    delete pShowAllInfo;
    pShowAllInfo=nullptr;
}
void MainWindow::showAllInfoBySearchName()
{
    pShowAllInfo=new showAllInfoDialog();

    pShowAllInfo->setWindowTitle("展示所有信息");
    pShowAllInfo->setData(_s,_i);
    pShowAllInfo->setTabInde(0);
    pShowAllInfo->exec();

    delete pShowAllInfo;
    pShowAllInfo=nullptr;
}
void MainWindow::showAllInfoBySearchId()
{
    pShowAllInfo=new showAllInfoDialog();

    pShowAllInfo->setWindowTitle("展示所有信息");
    pShowAllInfo->setData(_s,_i);
    pShowAllInfo->setTabInde(1);
    pShowAllInfo->exec();

    delete pShowAllInfo;
    pShowAllInfo=nullptr;
}



QString MainWindow::getUserName()
{
#if 1
    QStringList envVariables;
    envVariables << "USERNAME.*" << "USER.*" << "USERDOMAIN.*"
                 << "HOSTNAME.*" << "DOMAINNAME.*";
    QStringList environment = QProcess::systemEnvironment();
    foreach (QString string, envVariables) {
        int index = environment.indexOf(QRegExp(string));
        if (index != -1) {
            QStringList stringList = environment.at(index).split('=');
            if (stringList.size() == 2) {
                return stringList.at(1);
                break;
            }
        }
    }
    return "unknown";
#else
    QString userName = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    userName = userName.section("/", -1, -1);
    return userName;
#endif
}

QString MainWindow::getMachineName()
{
    QString localHostName = QHostInfo::localHostName();
        return localHostName;
}

void MainWindow::on_exitWithoutSaveButton_clicked()
{
    isSave=false;
    this->close();
}
