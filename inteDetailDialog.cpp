#include "inteDetailDialog.h"
#include "ui_inteDetailDialog.h"
#include"qtablewidget.h"
#include"qdebug.h"
#include"qmessagebox.h"
inteDetailDialog::inteDetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inteDetailDialog)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(false);

    QPalette pa(this->palette());
    pa.setColor(QPalette::Background,QColor(187,212,238));
    this->setPalette(pa);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

inteDetailDialog::~inteDetailDialog()
{
    delete ui;
}

void inteDetailDialog::setData(studentMana &_s, inteClassMana &_i)
{
    this->_s=_s;
    this->_i=_i;
}

void inteDetailDialog::setName(string inteClassName, string inteName)
{
    this->inteClassName=inteClassName;
    this->inteName=inteName;
}
void inteDetailDialog::showInfo()
{
    for(int i=ui->tableWidget->rowCount();i>0;i--)
    {
        ui->tableWidget->removeRow(i-1);
    }

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->inteClassNameLabel->setText(QString::fromStdString(this->inteClassName));
    ui->inteNameLabel->setText(QString::fromStdString(this->inteName));
    inteClass *inteClassTemp=_i.searchInteClassByInteClassName(this->inteClassName);
    inte *temp=inteClassTemp->searchInteByInteName(this->inteName);
    vector<int> stuNum=temp->getStudentSplNum();

    for(int i=0;i<stuNum.size();i++)
    {

        student* stuTemp=_s.searchStudentBySplNum(stuNum[i]);


        QTableWidgetItem *nameItem=new QTableWidgetItem();
        nameItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *idItem=new QTableWidgetItem();
        idItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *departmentItem=new QTableWidgetItem();
        departmentItem->setTextAlignment(Qt::AlignCenter);

        int row_count=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row_count);

        nameItem->setText(QString::fromStdString(stuTemp->getName()));
        idItem->setText(QString::number(stuTemp->getId()));

        QString de=QString::fromStdString(_s.numDepartmentMap.find(stuTemp->getDepartmentNum())->second);
        departmentItem->setText(de);


        ui->tableWidget->setItem(row_count,0,nameItem);
        ui->tableWidget->setItem(row_count,1,idItem);
        ui->tableWidget->setItem(row_count,2,departmentItem);

    }


}

void inteDetailDialog::on_addStuButton_clicked()
{
    pAddStu=new addStuForInteDialog();
    pAddStu->setWindowTitle("批量添加学生");
    pAddStu->setData(this->_s,this->_i);
    pAddStu->setName(this->inteClassName,this->inteName);
    pAddStu->isAdd=true;
    pAddStu->showInfo();


    pAddStu->exec();
    this->_s=pAddStu->_s;
    this->_i=pAddStu->_i;
    this->showInfo();

    delete pAddStu;
}

void inteDetailDialog::on_delStuButton_clicked()
{
    pAddStu=new addStuForInteDialog();
    pAddStu->setWindowTitle("批量删除学生");
    pAddStu->setData(this->_s,this->_i);
    pAddStu->setName(this->inteClassName,this->inteName);
    pAddStu->isAdd=false;
    pAddStu->showInfo();


    pAddStu->exec();
    this->_s=pAddStu->_s;
    this->_i=pAddStu->_i;
    this->showInfo();

    delete pAddStu;
}

void inteDetailDialog::on_stuDetailButton_clicked()
{
    bool isSelected=ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    if(isSelected)
    {

        QString selectName= ui->tableWidget->item( ui->tableWidget->currentItem()->row(),0)->text();

        string name=selectName.toStdString();
        pStuInfo=new stuInfoDialog();
        pStuInfo->setData(_s,_i);
        pStuInfo->setName(name);
        selectName+="的详细信息(信息禁止修改，修改请通过学生信息界面进入!)";
        pStuInfo->setWindowTitle(selectName);
        pStuInfo->initInfo();
        pStuInfo->buttonEnabled();

        pStuInfo->exec();
        /*this->_s=pStuInfo->_s;
        this->_i=pStuInfo->_i;
        */
        delete pStuInfo;

    }
    else
    {
        QMessageBox::warning(this,QString::fromUtf8("错误"),QString::fromUtf8("请单击选择一名学生后，进行详细信息查询！"));
    }
}

void inteDetailDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    this->on_stuDetailButton_clicked();
}
