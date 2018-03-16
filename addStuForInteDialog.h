#ifndef ADDSTUFORINTEDIALOG_H
#define ADDSTUFORINTEDIALOG_H

#include <QDialog>
#include"student.h"
#include"interestmana.h"
namespace Ui {
class addStuForInteDialog;
}

class addStuForInteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addStuForInteDialog(QWidget *parent = 0);
    ~addStuForInteDialog();

    inteClassMana _i;
    studentMana _s;
    void setData(studentMana &_s,inteClassMana &_i);
    void showInfo();
    void setName(string inteClassName,string inteName);
    bool isAdd;
    string inteName;
    string inteClassName;


private slots:
    void on_selectAllButton_clicked();

    void on_selectReverseButton_clicked();

    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::addStuForInteDialog *ui;
};

#endif // ADDSTUFORINTEDIALOG_H
