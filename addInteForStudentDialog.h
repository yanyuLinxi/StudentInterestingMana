#ifndef ADDINTEFORSTUDENTDIALOG_H
#define ADDINTEFORSTUDENTDIALOG_H

#include <QDialog>
#include"student.h"
#include"interestmana.h"
#include"qstandarditemmodel.h"

namespace Ui {
class addInteForStudentDialog;
}

class addInteForStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addInteForStudentDialog(QWidget *parent = 0);
    ~addInteForStudentDialog();

    studentMana _s;
    inteClassMana _i;

    vector<inteNumber> inteNum;
    string name;

    void setData(studentMana _s,inteClassMana _i);
    void setName(string name);
    void showInfo();
    bool isAdd;

private slots:
    void treeItemChanged(QStandardItem* item);
    void on_selectAllButton_clicked();

    void on_selectReverseButton_clicked();

    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::addInteForStudentDialog *ui;
   void treeItem_checkAllChild(QStandardItem* item,bool check);
   void treeItem_checkAllChild_recursion(QStandardItem* item,bool check);

    void treeItem_CheckChildChanged(QStandardItem *item);
   Qt::CheckState checkSibling(QStandardItem*item);

};

#endif // ADDINTEFORSTUDENTDIALOG_H
