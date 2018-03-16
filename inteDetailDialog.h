#ifndef INTEDETAILDIALOG_H
#define INTEDETAILDIALOG_H

#include <QDialog>
#include"student.h"
#include"interestmana.h"
#include"addStuForInteDialog.h"
#include"stuInfoDialog.h"
namespace Ui {
class inteDetailDialog;
}

class inteDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit inteDetailDialog(QWidget *parent = 0);
    ~inteDetailDialog();

    studentMana _s;
    inteClassMana _i;

    string inteName;
    string inteClassName;

    void setData(studentMana &_s,inteClassMana &_i);
    void setName(string inteClassName,string inteName);
    void showInfo();

private slots:
    void on_addStuButton_clicked();

    void on_delStuButton_clicked();

    void on_stuDetailButton_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::inteDetailDialog *ui;
    addStuForInteDialog *pAddStu;
    stuInfoDialog *pStuInfo;
};

#endif // INTEDETAILDIALOG_H
