#include "addstudentdialog.h"
#include "ui_addstudentdialog.h"
#include"qdebug.h"
#include"qmessagebox.h"
#include"string.h"
addStudentDialog::addStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStudentDialog)
{

    ui->setupUi(this);

    isNameEdit=false;
    isDepartmentEdit=false;
    isAgeEdit=false;
    isIdEdit=false;
    QIntValidator* ageValidator=new QIntValidator(0,1000,this);
    QIntValidator* idValidator=new QIntValidator(9999999,100000000,this);
    ui->ageEdit->setValidator(ageValidator);
    ui->idEdit->setValidator(idValidator);

    originalName=ui->nameEdit->text();


    QPalette pa(this->palette());
    pa.setColor(QPalette::Background,QColor(187,212,238));
    this->setPalette(pa);
}

void addStudentDialog::setData(studentMana _s)
{
    this->_s=_s;
}


addStudentDialog::~addStudentDialog()
{
    delete ui;
}

void addStudentDialog::on_CancelButton_clicked()
{
    this->close();
}

void addStudentDialog::setOriginalName(string originalName)
{
    this->originalName=QString::fromStdString(originalName);
    student *temp=_s.searchStudentByName(originalName);
    ui->nameEdit->setText(QString::fromStdString(temp->getName()));
    ui->idEdit->setText(QString::number(temp->getId()));
    if(temp->getSex()==QString("男").toStdString())
    {
        ui->sexComBox->setCurrentIndex(0);
    }
    else
    {
        ui->sexComBox->setCurrentIndex(1);
    }
    QString de=QString::fromStdString(_s.numDepartmentMap.find(temp->getDepartmentNum())->second);
    ui->departmentEdit->setText(de);
    ui->otherNoteEdit->setText(QString::fromStdString(temp->getOtherNote()));
    ui->ageEdit->setText(QString::number(temp->getAge()));
}

void addStudentDialog::on_OkButton_clicked()
{
            name=ui->nameEdit->text();
            age=ui->ageEdit->text().toInt();
            department=ui->departmentEdit->text();
            otherNote=ui->otherNoteEdit->toPlainText();
            switch (ui->sexComBox->currentIndex()) {
            case 0:
                sex="男";
                break;
            default:sex="女";
                break;
            }
            id=ui->idEdit->text().toInt();
    if(!name.isEmpty()&&age!=0&&!department.isEmpty()&&id!=0)
    {
       if(isAdd)
       {
           _s.addStudent(id,name.toStdString(),sex.toStdString(),age,department.toStdString(),otherNote.toStdString());
       }
       else
       {
           student *temp=_s.searchStudentByName(originalName.toStdString());
           int de=_s.departmentNumMap.find(department.toStdString())->second;
           temp->modifyInfo(id,name.toStdString(),sex.toStdString(),age,de,otherNote.toStdString());
       }

        this->close();

    }
    else
    {

        QMessageBox::warning(this,QString::fromUtf8("错误"),QString::fromUtf8("信息不完整，请输入完整信息！"));
    }
}

/*void addStudentDialog::on_nameEdit_textEdited(const QString &arg1)
{
    isNameEdit=true;
}

void addStudentDialog::on_idEdit_textEdited(const QString &arg1)
{
    isIdEdit=true;
}

void addStudentDialog::on_ageEdit_textEdited(const QString &arg1)
{
    isAgeEdit=true;
}

void addStudentDialog::on_departmentEdit_textEdited(const QString &arg1)
{
    isDepartmentEdit=true;
}
*/



