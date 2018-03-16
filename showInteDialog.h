#ifndef SHOWINTEDIALOG_H
#define SHOWINTEDIALOG_H

#include <QDialog>
#include<student.h>
#include<interestmana.h>
#include"addInteDialog.h"
#include"inteDetailDialog.h"
namespace Ui {
class showInteDialog;
}

class showInteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit showInteDialog(QWidget *parent = 0);
    ~showInteDialog();

    studentMana _s;
    inteClassMana _i;

    void setData(studentMana &_s,inteClassMana &_i);
    void showInte();

private slots:
    void on_addInteButton_clicked();

    void on_inteDetailButton_clicked();

    void on_inteTreeView_doubleClicked(const QModelIndex &index);

    void on_delInteButton_clicked();

    void on_inteTreeView_clicked(const QModelIndex &index);

private:
    Ui::showInteDialog *ui;

    addInteDialog *pAddInte;
    inteDetailDialog *pShowInteDetail;
    bool isSelect;
};

#endif // SHOWINTEDIALOG_H
