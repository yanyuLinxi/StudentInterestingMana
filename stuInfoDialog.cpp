#include "stuInfoDialog.h"
#include "ui_stuInfoDialog.h"
#include"qdebug.h"

stuInfoDialog::stuInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stuInfoDialog)
{
    ui->setupUi(this);
    ui->otherLabel->setWordWrap(true);


    ui->inteTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->inteTableWidget->setShowGrid(false);
    ui->inteTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置竖直滚动样式
    ui->inteTableWidget->horizontalHeader()->setHighlightSections(true);
    ui->inteTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->stuInfoWidget->horizontalHeader()->setVisible(false);//设置水平的表头不可见
    ui->inteTableWidget->verticalHeader()->setVisible(false);//设置竖直的表头不可见（左边那一列
    ui->inteTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为只可读


    QPalette pa(this->palette());
    pa.setColor(QPalette::Background,QColor(187,212,238));
    this->setPalette(pa);
}

void stuInfoDialog::buttonEnabled()
{
    ui->addInteButton->setVisible(false);
    ui->delInteButton->setVisible(false);
    ui->modifyButton->setVisible(false);
}

void stuInfoDialog::buttonOn()
{
    ui->addInteButton->setVisible(true);
    ui->delInteButton->setVisible(true);
    ui->modifyButton->setVisible(true);
}

stuInfoDialog::~stuInfoDialog()
{
    delete ui;
}

void stuInfoDialog::setData(studentMana &_s, inteClassMana &_i)
{
    this->_s=_s;
    this->_i=_i;
}

void stuInfoDialog::setName(string inputName)
{
    this->name=inputName;

}

void stuInfoDialog::initInfo()
{
    for(int i=ui->inteTableWidget->rowCount()-1;i>=0;i--)
    {
        ui->inteTableWidget->removeRow(i);
    }
    student *temp=_s.searchStudentByName(this->name);

    ui->nameLabel->setText(QString::fromStdString(temp->getName()));
    ui->idLabel->setText(QString::number(temp->getId()));
    ui->ageLabel->setText(QString::number(temp->getAge()));
    QString department=QString::fromStdString(_s.getDepartmentNameBySplNum(temp->getDepartmentNum()));
    ui->departmentLabel->setText(department);
    ui->otherLabel->setText(QString::fromStdString(temp->getOtherNote()));
    ui->sexLabel->setText(QString::fromStdString(temp->getSex()));

    vector<inteNumber>::iterator ite;
    for(ite=temp->inteNum.begin();ite!=temp->inteNum.end();ite++){
        int row_count=ui->inteTableWidget->rowCount();
        ui->inteTableWidget->insertRow(row_count);
        QTableWidgetItem *item=new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignCenter);
        item->setText(QString::fromStdString(_i.getInteClassNameBySplNum(ite->inteClass)));
        QTableWidgetItem *item2=new QTableWidgetItem();
        item2->setText(QString::fromStdString(_i.getInteNameBySplNum(ite->inteClass,ite->inte)));
        item2->setTextAlignment(Qt::AlignCenter);
        ui->inteTableWidget->setItem(row_count,0,item);
        ui->inteTableWidget->setItem(row_count,1,item2);
    }

}

void stuInfoDialog::on_addInteButton_clicked()
{
    pAddInteForStu=new addInteForStudentDialog();
    pAddInteForStu->isAdd=true;
    pAddInteForStu->setWindowTitle("添加兴趣");
    pAddInteForStu->setData(_s,_i);
    pAddInteForStu->setName(this->name);
    pAddInteForStu->showInfo();
    pAddInteForStu->exec();
    this->_s=pAddInteForStu->_s;
    this->_i=pAddInteForStu->_i;
    this->initInfo();
    delete pAddInteForStu;
}

void stuInfoDialog::on_delInteButton_clicked()
{
    pAddInteForStu=new addInteForStudentDialog();
    pAddInteForStu->isAdd=false;
    pAddInteForStu->setWindowTitle("删除兴趣");
    pAddInteForStu->setData(_s,_i);
    pAddInteForStu->setName(this->name);
    pAddInteForStu->showInfo();
     pAddInteForStu->exec();
    this->_s=pAddInteForStu->_s;
    this->_i=pAddInteForStu->_i;
    this->initInfo();
    delete pAddInteForStu;
}

void stuInfoDialog::on_modifyButton_clicked()
{
    pAddStu=new addStudentDialog();
    pAddStu->setWindowTitle("修改"+QString::fromStdString( this->name)+"的个人信息");
    pAddStu->setData(_s);
    pAddStu->isAdd=false;
    pAddStu->setOriginalName(this->name);
    pAddStu->exec();
    if(!pAddStu->name.isEmpty()){
        this->setName(pAddStu->name.toStdString());
        this->_s=pAddStu->_s;
        this->initInfo();
    }
    delete pAddStu;


}
