#include "addInteDialog.h"
#include "ui_addInteDialog.h"
#include"qmessagebox.h"
addInteDialog::addInteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addInteDialog)
{
    ui->setupUi(this);

    QPalette pa(this->palette());
    pa.setColor(QPalette::Background,QColor(187,212,238));
    this->setPalette(pa);

}

addInteDialog::~addInteDialog()
{
    delete ui;
}

void addInteDialog::on_inteClassCombBox_currentIndexChanged(int index)
{
    if(index==ui->inteClassCombBox->count()-1)
    {
        ui->inteClassLineEdit->setEnabled(true);
        ui->addInteClassLabel->setEnabled(true);
    }
    else
    {
        ui->inteClassLineEdit->setEnabled(false);
        ui->addInteClassLabel->setEnabled(false);
    }
}
void addInteDialog::setData(inteClassMana &_i)
{
    this->_i=_i;
}

void addInteDialog::showInte()
{
    ui->inteClassCombBox->addItem(QString(""));
    vector<inteClass>::iterator classIte;
    vector<inteClass> classVector=_i.inteClassVector;
    for(classIte=classVector.begin();classIte!=classVector.end();classIte++)
    {
        ui->inteClassCombBox->addItem(QString::fromStdString(classIte->getInteClassName()));
    }
    ui->inteClassCombBox->addItem(QString("增加新项"));
    ui->inteClassLineEdit->setEnabled(false);
    ui->addInteClassLabel->setEnabled(false);

}



void addInteDialog::on_cancelButton_clicked()
{
    this->close();
}

void addInteDialog::on_OkButton_clicked()
{
    QString inputInteClassName=ui->inteClassLineEdit->text();
    QString inputInteName=ui->inteLineEdit->text();
    if(ui->inteClassCombBox->currentIndex()==0)
    {
        QMessageBox::warning(this,QString::fromUtf8("错误"),QString::fromUtf8("请选择一个兴趣类或新增一个兴趣类！"));
    }
    else if(ui->inteClassCombBox->currentIndex()==ui->inteClassCombBox->count()-1&&inputInteClassName.isEmpty())
    {
        QMessageBox::warning(this,QString::fromUtf8("错误"),QString::fromUtf8("请输入兴趣类名称"));
    }
    else if(inputInteName.isEmpty())
    {
        QMessageBox::warning(this,QString::fromUtf8("错误"),QString::fromUtf8("请输入兴趣名称！"));
    }
    else if(ui->inteClassLineEdit->isEnabled()==false)
    {
        inputInteClassName=ui->inteClassCombBox->currentText();
        _i.addInte(inputInteClassName.toStdString(),inputInteName.toStdString());
        ui->inteClassCombBox->clear();
        this->close();
    }
    else
    {
        _i.addInte(inputInteClassName.toStdString(),inputInteName.toStdString());
        ui->inteClassCombBox->clear();
        this->close();
    }
}
