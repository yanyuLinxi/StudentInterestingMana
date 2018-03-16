#include "addStuForInteDialog.h"
#include "ui_addStuForInteDialog.h"
#include"qstandarditemmodel.h"
addStuForInteDialog::addStuForInteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStuForInteDialog)
{
    ui->setupUi(this);
    ui->stuTreeView->setEditTriggers(false);

    QPalette pa(this->palette());
    pa.setColor(QPalette::Background,QColor(187,212,238));
    this->setPalette(pa);
}

addStuForInteDialog::~addStuForInteDialog()
{
    delete ui;
}

void addStuForInteDialog::setData(studentMana &_s, inteClassMana &_i)
{
    this->_s=_s;
    this->_i=_i;
}

void addStuForInteDialog::setName(string inteClassName,string inteName)
{
    this->inteName=inteName;
    this->inteClassName=inteClassName;
}

void addStuForInteDialog::showInfo()
{

    QStandardItemModel* model=new QStandardItemModel(ui->stuTreeView);
   // QObject::connect(model,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(treeItemChanged(QStandardItem*)));
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("学生"));
    ui->stuTreeView->setModel(model);

    vector<student> stuVecTemp=_s.stu;
    vector<student>::iterator stuIte;

    inte* inteTemp=_i.searchInteClassByInteClassName(this->inteClassName)->searchInteByInteName(this->inteName);
    vector<int> stuNumVec=inteTemp->getStudentSplNum();
    for(stuIte=stuVecTemp.begin();stuIte!=stuVecTemp.end();stuIte++)
    {
        if(isAdd){
            vector<int>::iterator ite;
            ite=std::find(stuNumVec.begin(),stuNumVec.end(),stuIte->getSplNumber());
            if(ite==stuNumVec.end())
            {
                QStandardItem* item=new QStandardItem(QString::fromStdString(stuIte->getName()));
                item->setCheckable(true);
                item->setCheckState(Qt::Unchecked);
                item->setTristate(false);
                model->appendRow(item);
            }
        }
        else
        {
            vector<int>::iterator ite;
            ite=std::find(stuNumVec.begin(),stuNumVec.end(),stuIte->getSplNumber());
            if(ite!=stuNumVec.end())
            {
                QStandardItem* item=new QStandardItem(QString::fromStdString(stuIte->getName()));
                item->setCheckable(true);
                item->setCheckState(Qt::Unchecked);
                item->setTristate(false);
                model->appendRow(item);
            }
        }
    }



    ui->stuTreeView->expandAll();

}

void addStuForInteDialog::on_selectAllButton_clicked()
{
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->stuTreeView->model());

    for(int _r=0;_r<model->rowCount();_r++)
    {
        QModelIndex topIndex =model->index(_r,0);//ui->inteTreeView->indexAt(QPoint(_r,0));
        QStandardItem* topItem = model->itemFromIndex(topIndex);
        topItem->setCheckState(Qt::Checked);
    }
}

void addStuForInteDialog::on_selectReverseButton_clicked()
{
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->stuTreeView->model());

    for(int _r=0;_r<model->rowCount();_r++)
    {
        QModelIndex topIndex =model->index(_r,0);//ui->inteTreeView->indexAt(QPoint(_r,0));
        QStandardItem* topItem = model->itemFromIndex(topIndex);

        topItem->setCheckState(topItem->checkState()==Qt::Checked?Qt::Unchecked : Qt::Checked);
    }
}

void addStuForInteDialog::on_cancelButton_clicked()
{
    this->close();
}

void addStuForInteDialog::on_okButton_clicked()
{
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->stuTreeView->model());

    for(int _r=0;_r<model->rowCount();_r++)
    {
        QModelIndex topIndex =model->index(_r,0);//ui->inteTreeView->indexAt(QPoint(_r,0));
        QStandardItem* topItem = model->itemFromIndex(topIndex);
        int inteClassNum=_i.getInteClassSplNumByName(this->inteClassName);
        int inteNum=_i.getInteSplNumByName(this->inteClassName,this->inteName);
        student* temp=_s.searchStudentByName(topIndex.data().toString().toStdString());
        inte* inteTemp=_i.searchInteClassByInteClassName(this->inteClassName)->searchInteByInteName(this->inteName);

        if(topItem->checkState()==Qt::Checked){
           if(isAdd){
                  temp->addInte(inteClassNum,inteNum);
                 inteTemp->addStudentNum(temp->getSplNumber());
                }
           else
           {
               temp->delInte(inteClassNum,inteNum);
               inteTemp->delStudentNum(temp->getSplNumber());
           }
        }

    }

   this->close();
}
