#ifndef ADDINTEDIALOG_H
#define ADDINTEDIALOG_H

#include <QDialog>
#include<interestmana.h>


namespace Ui {
class addInteDialog;
}

class addInteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addInteDialog(QWidget *parent = 0);
    ~addInteDialog();

    inteClassMana _i;

    void setData(inteClassMana &_i);
    void showInte();
private slots:
    void on_inteClassCombBox_currentIndexChanged(int index);

    void on_cancelButton_clicked();

    void on_OkButton_clicked();

private:
    Ui::addInteDialog *ui;

};

#endif // ADDINTEDIALOG_H
