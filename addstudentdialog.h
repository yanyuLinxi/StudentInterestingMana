#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>
#include"student.h"

namespace Ui {
class addStudentDialog;

}

class addStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addStudentDialog(QWidget *parent = 0);
    ~addStudentDialog();
    int id;
    QString originalName;
    QString name;
    QString department;
    QString otherNote;
    int age;
    QString sex;

    studentMana _s;
    bool isAdd;

    void setData(studentMana _s);
    void setOriginalName(string originalName);


private slots:
    void on_CancelButton_clicked();

    void on_OkButton_clicked();

   /* void on_nameEdit_textEdited(const QString &arg1);

    void on_idEdit_textEdited(const QString &arg1);

    void on_ageEdit_textEdited(const QString &arg1);

    void on_departmentEdit_textEdited(const QString &arg1);*/


private:
    Ui::addStudentDialog *ui;

    bool isNameEdit;
    bool isIdEdit;
    bool isAgeEdit;
    bool isDepartmentEdit;

};

#endif // ADDSTUDENTDIALOG_H
