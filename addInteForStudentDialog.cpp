#include "addInteForStudentDialog.h"
#include "ui_addInteForStudentDialog.h"
#include"qstandarditemmodel.h"
#include"qdebug.h"

addInteForStudentDialog::addInteForStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addInteForStudentDialog)
{
    ui->setupUi(this);

    ui->inteTreeView->setEditTriggers(0);//设置树不可读

    QPalette pa(this->palette());
    pa.setColor(QPalette::Background,QColor(187,212,238));
    this->setPalette(pa);
}

addInteForStudentDialog::~addInteForStudentDialog()
{
    delete ui;
}


void addInteForStudentDialog::setData(studentMana _s, inteClassMana _i)
{
    this->_s=_s;
    this->_i=_i;
}

void addInteForStudentDialog::showInfo()
{
    QStandardItemModel* model=new QStandardItemModel(ui->inteTreeView);
    QObject::connect(model,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(treeItemChanged(QStandardItem*)));
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("兴趣类"));
    ui->inteTreeView->setModel(model);
    ui->inteTreeView->expandAll();
    vector<inte> _inteVector;
    vector<inteClass> _inteClassVector=_i.getInteClassVector();


    vector<inte>::iterator _inteIte;
    vector<inteClass>::iterator _inteClassIte;

   for (_inteClassIte = _inteClassVector.begin(); _inteClassIte != _inteClassVector.end(); _inteClassIte++)
   {
         QStandardItem* item=new QStandardItem(QString::fromStdString(_inteClassIte->getInteClassName()));//添加类
         // model->setItem(model->indexFromItem(item).row(),1,new QStandardItem( QString::number(0)));//添加右列信息
          model->appendRow(item);
          item->setCheckable(true);
          item->setCheckState(Qt::Unchecked);
          item->setTristate(true);
         _inteVector = _inteClassIte->getInteVector();
         for (_inteIte = _inteVector.begin(); _inteIte != _inteVector.end(); _inteIte++)
         {
              inteNumber temp(_inteClassIte->getInteClassSplNum(),_inteIte->getInteSplNum());
              vector<inteNumber>::iterator inteNumIte;
              inteNumIte=std::find(inteNum.begin(),inteNum.end(),temp);
              if(isAdd){
                if(inteNumIte==inteNum.end()){
                 QStandardItem* itemChild=new QStandardItem(QString::fromStdString(_inteIte->getInteName()));

                  itemChild->setCheckable(true);
                 itemChild->setCheckState(Qt::Unchecked);
                 itemChild->setTristate(false);
                item->appendRow(itemChild);

                 }
              }
              else
              {
                  if(inteNumIte!=inteNum.end()){
                   QStandardItem* itemChild=new QStandardItem(QString::fromStdString(_inteIte->getInteName()));

                    itemChild->setCheckable(true);
                   itemChild->setCheckState(Qt::Unchecked);
                   itemChild->setTristate(false);
                  item->appendRow(itemChild);

                   }
              }

        }
         if(!item->hasChildren())
         {
             model->removeRow(model->rowCount()-1);
         }
    }
    ui->inteTreeView->expandAll();
}

void addInteForStudentDialog::treeItemChanged ( QStandardItem * item )
{
    if ( item == nullptr )
     return ;
    if ( item->isCheckable ())
    {
        //如果条目是存在复选框的，那么就进行下面的操作
        Qt::CheckState state = item->checkState (); //获取当前的选择状态
        if ( item ->isTristate ())
        {
             //如果条目是三态的，说明可以对子目录进行全选和全不选的设置
            if ( state != Qt :: PartiallyChecked )
            {
                //当前是选中状态，需要对其子项目进行全选
                treeItem_checkAllChild ( item , state == Qt:: Checked ? true : false );
            }
        }
        else
        {
            //说明是两态的，两态会对父级的三态有影响
            //判断兄弟节点的情况
            treeItem_CheckChildChanged ( item );
        }
    }
}

void addInteForStudentDialog::treeItem_checkAllChild(QStandardItem * item, bool check)
{
    if(item == nullptr)
        return;
    int rowCount = item->rowCount();
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}
void addInteForStudentDialog::treeItem_checkAllChild_recursion(QStandardItem * item,bool check)
{
    if(item == nullptr)
        return;
    int rowCount = item->rowCount();
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}

void addInteForStudentDialog::treeItem_CheckChildChanged(QStandardItem * item)
{
    if(nullptr == item)
        return;
    Qt::CheckState siblingState = checkSibling(item);
    QStandardItem * parentItem = item->parent();
    if(nullptr == parentItem)
        return;
    if(Qt::PartiallyChecked == siblingState)
    {
        if(parentItem->isCheckable() && parentItem->isTristate())
            parentItem->setCheckState(Qt::PartiallyChecked);
    }
    else if(Qt::Checked == siblingState)
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Checked);
    }
    else
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Unchecked);
    }
    treeItem_CheckChildChanged(parentItem);
}

Qt::CheckState addInteForStudentDialog::checkSibling(QStandardItem * item)
{
    //先通过父节点获取兄弟节点
    QStandardItem * parent = item->parent();
    if(nullptr == parent)
        return item->checkState();
    int brotherCount = parent->rowCount();
    int checkedCount(0),unCheckedCount(0);
    Qt::CheckState state;
    for(int i=0;i<brotherCount;++i)
    {
        QStandardItem* siblingItem = parent->child(i);
        state = siblingItem->checkState();
        if(Qt::PartiallyChecked == state)
            return Qt::PartiallyChecked;
        else if(Qt::Unchecked == state)
            ++unCheckedCount;
        else
            ++checkedCount;
        if(checkedCount>0 && unCheckedCount>0)
            return Qt::PartiallyChecked;
    }
    if(unCheckedCount>0)
        return Qt::Unchecked;
    return Qt::Checked;
}


void addInteForStudentDialog::setName(string name)
{
    this->name=name;
    student* temp=_s.searchStudentByName(this->name);
    this->inteNum=temp->inteNum;
}

void addInteForStudentDialog::on_selectAllButton_clicked()
{
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->inteTreeView->model());

    for(int _r=0;_r<model->rowCount();_r++)
    {
        QModelIndex topIndex =model->index(_r,0);//ui->inteTreeView->indexAt(QPoint(_r,0));
        QStandardItem* topItem = model->itemFromIndex(topIndex);
        topItem->setCheckState(Qt::Checked);
    }

}

void addInteForStudentDialog::on_selectReverseButton_clicked()
{
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->inteTreeView->model());

    for(int _r=0;_r<model->rowCount();_r++)
    {
        QModelIndex topIndex =model->index(_r,0);//ui->inteTreeView->indexAt(QPoint(_r,0));
        QStandardItem* topItem = model->itemFromIndex(topIndex);
        for(int i=0;i<topItem->rowCount();i++)
        {
            QStandardItem* childItem=topItem->child(i);
            childItem->setCheckState(childItem->checkState()==Qt::Unchecked?Qt::Checked : Qt::Unchecked);
        }
    }
}

void addInteForStudentDialog::on_cancelButton_clicked()
{

    this->close();
}

void addInteForStudentDialog::on_okButton_clicked()
{
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->inteTreeView->model());

    for(int _r=0;_r<model->rowCount();_r++)
    {
        QModelIndex topIndex =model->index(_r,0);//ui->inteTreeView->indexAt(QPoint(_r,0));
        QStandardItem* topItem = model->itemFromIndex(topIndex);
        for(int i=0;i<topItem->rowCount();i++)
        {
            QStandardItem* childItem=topItem->child(i);
            QModelIndex childIndex=topIndex.child(i,0);

           if(childItem->checkState()==Qt::Checked)
           {

                if(isAdd){
                    _s.addInte(this->name,_i.getInteClassSplNumByName(topIndex.data().toString().toStdString()),_i.getInteSplNumByName(topIndex.data().toString().toStdString(),childIndex.data().toString().toStdString()));
                    _i.addStudentNum(topIndex.data().toString().toStdString(),childIndex.data().toString().toStdString(),student::getSplNumberByName(this->name));
                }
                else{
                    _s.delInte(this->name,_i.getInteClassSplNumByName(topIndex.data().toString().toStdString()),_i.getInteSplNumByName(topIndex.data().toString().toStdString(),childIndex.data().toString().toStdString()));
                    _i.delStudentNum(topIndex.data().toString().toStdString(),childIndex.data().toString().toStdString(),student::getSplNumberByName(this->name));
                }
           }
        }
    }

   this->close();
}


