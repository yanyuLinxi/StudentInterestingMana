#pragma once
#ifndef STUINFODIALOG_H
#define STUINFODIALOG_H

#include <QDialog>
#include<interestmana.h>
#include<student.h>
#include"addInteForStudentDialog.h"
#include"addstudentdialog.h"
namespace Ui {
class stuInfoDialog;
}

class stuInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit stuInfoDialog(QWidget *parent = 0);
    ~stuInfoDialog();
    void setData(studentMana &_s,inteClassMana &_i);
    void setName(string inputName);
    void initInfo();
    void buttonEnabled();
    void buttonOn();
    studentMana _s;
    inteClassMana _i;
private slots:
    void on_addInteButton_clicked();

    void on_delInteButton_clicked();

    void on_modifyButton_clicked();

private:
    Ui::stuInfoDialog *ui;

    string name;
    addInteForStudentDialog* pAddInteForStu;
    addStudentDialog *pAddStu;
};

#endif // STUINFODIALOG_H
