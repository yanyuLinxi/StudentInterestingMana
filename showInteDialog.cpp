#include "showInteDialog.h"
#include "ui_showInteDialog.h"
#include"qstandarditemmodel.h"
#include"qdebug.h"
#include"qmessagebox.h"

showInteDialog::showInteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showInteDialog)
{
    isSelect=false;
    ui->setupUi(this);
    ui->inteTreeView->setEditTriggers(0);//设置树不可读

    QPalette pa(this->palette());
    pa.setColor(QPalette::Background,QColor(187,212,238));
    this->setPalette(pa);

    ui->introLabel->setWordWrap(true);
    ui->inteTreeView->setFocus();

}

showInteDialog::~showInteDialog()
{
    delete ui;
}

void showInteDialog::setData(studentMana &_s, inteClassMana &_i)
{
    this->_s=_s;
    this->_i=_i;

}

void showInteDialog::showInte()
{


    QStandardItemModel* model=new QStandardItemModel(ui->inteTreeView);

    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("兴趣类")<<QStringLiteral("人数"));

    ui->inteTreeView->setModel(model);



    vector<inte> _inteVector;
    vector<inteClass> _inteClassVector=_i.getInteClassVector();
    vector<int> _studentVector;

    vector<inte>::iterator _inteIte;
    vector<inteClass>::iterator _inteClassIte;

    for (_inteClassIte = _inteClassVector.begin(); _inteClassIte != _inteClassVector.end(); _inteClassIte++)
    {
        QStandardItem* item=new QStandardItem(QString::fromStdString(_inteClassIte->getInteClassName()));//添加类名
        // model->setItem(model->indexFromItem(item).row(),1,new QStandardItem( QString::number(0)));//添加右列信息
        model->appendRow(item);
        _inteVector = _inteClassIte->getInteVector();
        for (_inteIte = _inteVector.begin(); _inteIte != _inteVector.end(); _inteIte++)
        {
            QStandardItem* itemChild=new QStandardItem(QString::fromStdString(_inteIte->getInteName()));
            item->appendRow(itemChild);
            item->setChild(itemChild->index().row(),1,new QStandardItem(QString::number(_inteIte->sumInteStudent)));

        }
    }
    ui->inteTreeView->expandAll();
}

void showInteDialog::on_addInteButton_clicked()
{
    pAddInte=new addInteDialog();
    pAddInte->setWindowTitle("添加兴趣");
    pAddInte->setData(_i);
    pAddInte->showInte();
    pAddInte->exec();
    _i=pAddInte->_i;
    showInte();
    delete pAddInte;
}

void showInteDialog::on_inteDetailButton_clicked()
{
    QStandardItemModel* model=static_cast<QStandardItemModel*>(ui->inteTreeView->model());
    QModelIndex currentIndex=ui->inteTreeView->currentIndex();
    //QStandardItem* currentItem=model->itemFromIndex(currentIndex);
    currentIndex=currentIndex.sibling(currentIndex.row(),0);
    QString curIndexParentName=currentIndex.parent().data().toString();
    QString curIndexName=currentIndex.data().toString();
    if(curIndexParentName.isEmpty())
    {
      QMessageBox::warning(this,QString::fromUtf8("错误"),QString::fromUtf8("请选择一项兴趣进行详细查询！"));
    }
    else
    {
        pShowInteDetail=new inteDetailDialog();
        pShowInteDetail->setWindowTitle(curIndexName+"详细信息");
        pShowInteDetail->setData(this->_s,this->_i);
        pShowInteDetail->setName(curIndexParentName.toStdString(),curIndexName.toStdString());
        pShowInteDetail->showInfo();
        pShowInteDetail->exec();
        this->_s=pShowInteDetail->_s;
        this->_i=pShowInteDetail->_i;

        this->showInte();

        delete pShowInteDetail;
    }
}

void showInteDialog::on_inteTreeView_doubleClicked(const QModelIndex &index)
{
    this->on_inteDetailButton_clicked();
}

void showInteDialog::on_delInteButton_clicked()
{
    QStandardItemModel* model=static_cast<QStandardItemModel*>(ui->inteTreeView->model());
    QModelIndex currentIndex=ui->inteTreeView->currentIndex();
    QStandardItem* parentItem = model->itemFromIndex(currentIndex);
    //QStandardItem* currentItem=model->itemFromIndex(currentIndex);
    currentIndex=currentIndex.sibling(currentIndex.row(),0);
    QString curIndexParentName=currentIndex.parent().data().toString();
    QString curIndexName=currentIndex.data().toString();

    if(curIndexName.isEmpty()||!isSelect)
    {
        QMessageBox::warning(this,QString::fromUtf8("错误"),QString::fromUtf8("请选择一项兴趣或兴趣类进行删除!"));
    }
    else{
    if(curIndexParentName.isEmpty())
    {
        for(int i=0;i<parentItem->rowCount();i++){
             QModelIndex childIndex=currentIndex.child(i,0);
             inteClass* inteClassTemp=_i.searchInteClassByInteClassName(curIndexName.toStdString());
             inte* temp=inteClassTemp->searchInteByInteName(childIndex.data().toString().toStdString());
             vector<int> stuNumVec=temp->getStudentSplNum();
             for(int i=0;i<stuNumVec.size();i++)
             {
                 student* stuTemp= _s.searchStudentBySplNum(stuNumVec[i]);
                 stuTemp->delInte(inteClassTemp->getInteClassSplNum(),temp->getInteSplNum());
             }
            inteClassTemp->delInteByName(childIndex.data().toString().toStdString());
        }
        _i.delInteClassByName(curIndexName.toStdString());
        QMessageBox::information(this,QString::fromUtf8("移除成功"),QString::fromUtf8("成功移除兴趣类！"));
        this->showInte();
    }
    else
    {
         inteClass* inteClassTemp=_i.searchInteClassByInteClassName(curIndexParentName.toStdString());
         inte* temp=inteClassTemp->searchInteByInteName(curIndexName.toStdString());
         vector<int> stuNumVec=temp->getStudentSplNum();
         for(int i=0;i<stuNumVec.size();i++)
         {
             student* stuTemp= _s.searchStudentBySplNum(stuNumVec[i]);
             stuTemp->delInte(inteClassTemp->getInteClassSplNum(),temp->getInteSplNum());
         }
        inteClassTemp->delInteByName(curIndexName.toStdString());
         QMessageBox::information(this,QString::fromUtf8("移除成功"),QString::fromUtf8("成功移除兴趣！"));

        this->showInte();


    }
    }

}

void showInteDialog::on_inteTreeView_clicked(const QModelIndex &index)
{
    isSelect=true;
}
