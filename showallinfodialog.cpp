#include "showallinfodialog.h"
#include "ui_showallinfodialog.h"
#include"qtableview.h"
#include <QStandardItemModel>
#include<qdebug.h>
#include<qmessagebox.h>
#include<algorithm>

#include<QCollator>
#include<QLocale>



showAllInfoDialog::showAllInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showAllInfoDialog)
{
    ui->setupUi(this);
    ui->stuInfoWidget->horizontalHeader()->setStretchLastSection(true);
    ui->stuInfoWidget->setShowGrid(false);
    ui->stuInfoWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置竖直滚动样式
    ui->stuInfoWidget->horizontalHeader()->setHighlightSections(true);
    ui->stuInfoWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->stuInfoWidget->horizontalHeader()->setVisible(false);//设置水平的表头不可见
    ui->stuInfoWidget->verticalHeader()->setVisible(false);//设置竖直的表头不可见（左边那一列
    ui->stuInfoWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为只可读

    QIntValidator* validator=new QIntValidator(9999999,100000000,this);
    ui->idLineEdit->setValidator(validator);


    QPalette pa(this->palette());
    pa.setColor(QPalette::Background,QColor(187,212,238));
    this->setPalette(pa);
    ui->infoLabel->setWordWrap(true);
}

void showAllInfoDialog::setTabInde(int index)
{
    this->tabIndex=index;
    ui->searchTabWidget->setCurrentIndex(index);
}

showAllInfoDialog::~showAllInfoDialog()
{

    delete ui;
}

void showAllInfoDialog::getAllInfoSlot()
{

}

void showAllInfoDialog::setData(studentMana &_s, inteClassMana &_i)
{
    this->_s=_s;
    this->_i=_i;
    showInfoByVector(_s.stu);


}

void showAllInfoDialog::sortByChinese(vector<student> &stu)
{
    //按照中文排序，有点麻烦，暂且放下不写
   /* QLocale cn(QLocale::Chinese);
    QCollator collator(cn);
    QStringList stringlist;
    vector<student>::iterator ite;
    for(ite=stu.begin();ite!=stu.end();ite++)
    {
        QString temp=QString::fromStdString(stu.getName());
        stringlist.push_back(temp);
    }
    std::sort(stringlist.begin(),stringlist.end(),collator);
    QStringListIterator strlistIte;
    vector<student> stuTemp;
    for(strlistIte=stringlist.begin();strlistIte!=stringlist.end();strlistIte++)
    {
        student *temp=_s.se
    }
    */
}

void showAllInfoDialog::showInfoByVector(vector<student> &temp)
{
    this->showTableClear();
    vector<student>::iterator ite;



    for(ite=temp.begin();ite!=temp.end();ite++)
    {
        int row_count=ui->stuInfoWidget->rowCount();
     QTableWidgetItem *itemNum=new QTableWidgetItem();
     itemNum->setTextAlignment(Qt::AlignCenter);
     QTableWidgetItem *itemName=new QTableWidgetItem();
     itemName->setTextAlignment(Qt::AlignCenter);
     QTableWidgetItem *itemId=new QTableWidgetItem();
     itemId->setTextAlignment(Qt::AlignCenter);
     QTableWidgetItem *itemSex=new QTableWidgetItem();
     itemSex->setTextAlignment(Qt::AlignCenter);
     QTableWidgetItem *itemDepartment=new QTableWidgetItem();
     itemDepartment->setTextAlignment(Qt::AlignCenter);


         ui->stuInfoWidget->insertRow(row_count);
         itemNum->setText(QString::number(row_count+1));
         itemName->setText(QString::fromStdString(ite->getName()));
         itemId->setText(QString::number(ite->getId()));
         itemSex->setText(QString::fromStdString(ite->getSex()));
         itemDepartment->setText(QString::fromStdString(_s.numDepartmentMap.find(ite->getDepartmentNum())->second));
         ui->stuInfoWidget->setItem(row_count,0,itemNum);
         ui->stuInfoWidget->setItem(row_count,1,itemName);
         ui->stuInfoWidget->setItem(row_count,2,itemId);
        ui->stuInfoWidget->setItem(row_count,3,itemSex);
        ui->stuInfoWidget->setItem(row_count,4,itemDepartment);


    }
}

void showAllInfoDialog::on_searchButton_clicked()
{
    QString inputDepartmentName=ui->departmentNameLineEdit->text();
    string departmentName=inputDepartmentName.toStdString();
    vector<student> temp=_s.searchStudentByDepartmentName(departmentName);
    if(temp.empty())
    {
         QMessageBox::warning(this,QString::fromUtf8("错误"),QString::fromUtf8("该专业不存在，请检查后重新输入！"));
    }
    else{
        showInfoByVector(temp);
    }
}

void showAllInfoDialog::showTableClear()//清空tableView
{
    //ui->stuInfoWidget->clear();
    for(int i=ui->stuInfoWidget->rowCount();i>0;i--)
    {
        ui->stuInfoWidget->removeRow(i-1);
    }
}

void showAllInfoDialog::on_searchButton_2_clicked()
{
    QString inputName=ui->nameLineEdit->text();
    string name=inputName.toStdString();
    student *stuTemp=_s.searchStudentByName(name);
    if(stuTemp==nullptr)
    {
      QMessageBox::warning(this,QString::fromUtf8("错误"),QString::fromUtf8("该学生姓名不存在，请检查后重新输入！"));
    }
    else{
        vector<student> temp;
        temp.push_back(*stuTemp);
        this->showInfoByVector(temp);
    }
}

void showAllInfoDialog::on_pushButton_clicked()
{
    this->showInfoByVector(_s.stu);
}

void showAllInfoDialog::on_searchByIdButton_clicked()
{
    QString inputId=ui->idLineEdit->text();
    int id=inputId.toInt();
    student *stuTemp=_s.searchStudentById(id);
    if(stuTemp==nullptr)
    {
        QMessageBox::warning(this,QString::fromUtf8("错误"),QString::fromUtf8("查无此人，请确定后重新输入！"));
    }
    else
    {
        vector<student> temp;
        temp.push_back(*stuTemp);
        this->showInfoByVector(temp);
    }
}

void showAllInfoDialog::on_searchStuDetailButton_clicked()
{

    //查看学生详细信息
    bool isSelected=ui->stuInfoWidget->isItemSelected(ui->stuInfoWidget->currentItem());
    if(isSelected)
    {

        QString selectName= ui->stuInfoWidget->item( ui->stuInfoWidget->currentItem()->row(),1)->text();
        string name=selectName.toStdString();
        pStuInfo=new stuInfoDialog();
        pStuInfo->setData(_s,_i);
        pStuInfo->setName(name);
        selectName+="的详细信息";
        pStuInfo->setWindowTitle(selectName);
        pStuInfo->initInfo();


        pStuInfo->exec();
        this->_s=pStuInfo->_s;
        this->_i=pStuInfo->_i;
        this->showInfoByVector(_s.stu);
        delete pStuInfo;

    }
    else
    {
        QMessageBox::warning(this,QString::fromUtf8("错误"),QString::fromUtf8("请单击选择一名学生后，进行详细信息查询！"));
    }
}

void showAllInfoDialog::on_stuInfoWidget_doubleClicked(const QModelIndex &index)
{
    this->on_searchStuDetailButton_clicked();
}

void showAllInfoDialog::on_delStuButton_clicked()
{
    //查看学生详细信息
    bool isSelected=ui->stuInfoWidget->isItemSelected(ui->stuInfoWidget->currentItem());
    if(isSelected)
    {

        QString selectName= ui->stuInfoWidget->item( ui->stuInfoWidget->currentItem()->row(),1)->text();
        string name=selectName.toStdString();
        student* temp=_s.searchStudentByName(name);
        vector<inteNumber> numVector=temp->inteNum;
        vector<inteNumber>::iterator ite;
        for(ite=numVector.begin();ite!=numVector.end();ite++)
        {
            string inteClass=_i.getInteClassNameBySplNum(ite->inteClass);
            string inte=_i.getInteNameBySplNum(ite->inteClass,ite->inte);
            _i.delStudentNum(inteClass,inte,temp->getSplNumber());
        }
        _s.delStudentByName(name);

        this->showInfoByVector(_s.stu);
        QMessageBox::information(this,QString::fromUtf8("删除成功"),QString::fromUtf8("成功移除信息！"));


    }
    else
    {
        QMessageBox::warning(this,QString::fromUtf8("错误"),QString::fromUtf8("请单击选择一名学生后，进行删除该学生信息！"));
    }
}

void showAllInfoDialog::on_addButton_clicked()
{
    pAddStu=new addStudentDialog();
    pAddStu->setData(_s);
    pAddStu->isAdd=true;
    pAddStu->setWindowTitle("添加新学生信息");
    pAddStu->exec();
    this->_s=pAddStu->_s;
    this->showInfoByVector(_s.stu);

    delete pAddStu;

}
