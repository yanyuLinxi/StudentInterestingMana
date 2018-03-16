#ifndef SHOWALLINFODIALOG_H
#define SHOWALLINFODIALOG_H
#include"student.h"
#include"interestmana.h"
#include"stuInfoDialog.h"
#include <QDialog>
#include"addstudentdialog.h"
namespace Ui {
class showAllInfoDialog;
}

class showAllInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit showAllInfoDialog(QWidget *parent = 0);
    ~showAllInfoDialog();
    void setData(studentMana &_s,inteClassMana &_i);
    void setTabInde(int index);
    void sortByChinese(vector<student> &stu);

    studentMana _s;
    inteClassMana _i;
public slots:
    void getAllInfoSlot();
private slots:
    void on_searchButton_clicked();

    void on_searchButton_2_clicked();

    void on_pushButton_clicked();

    void on_searchByIdButton_clicked();

    void on_searchStuDetailButton_clicked();

    void on_stuInfoWidget_doubleClicked(const QModelIndex &index);

    void on_delStuButton_clicked();

    void on_addButton_clicked();

private:
    Ui::showAllInfoDialog *ui;
    void showInfoByVector(vector<student> &temp);
    void showTableClear();
    stuInfoDialog *pStuInfo;
    int tabIndex;
    addStudentDialog *pAddStu;
};

#endif // SHOWALLINFODIALOG_H
