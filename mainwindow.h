#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"Student.h"
#include"interestmana.h"
#include"addstudentdialog.h"
#include"showallinfodialog.h"
#include <QMainWindow>
#include"showInteDialog.h"
#include"addInteDialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setData(studentMana &_s,inteClassMana &_i);
    void set_i(inteClassMana &_i);
    void set_s(studentMana &_s);


    studentMana _s;
    inteClassMana _i;

    QString lastInfo;
    QString showInfo;


    QString stuName;
    int stuId;
    QString stuDepartment;
    int stuAge;
    QString stuOtherNote;
    QString stuSex;
signals:

private slots:
    void addNewStudentSlot();
    void addInteSlot();
    void on_pushButton_clicked();
    void showAllInfo();

    void showAllInfoBySearchName();
    void showAllInfoBySearchId();
    void showAllInfoBySearchDe();
    void showInteSlot();
    void useInfoSlot();


    void on_exitWithoutSaveButton_clicked();

private:
    Ui::MainWindow *ui;
    showAllInfoDialog *pShowAllInfo;
    addStudentDialog *pAddStu;
    showInteDialog *pShowInte;
    addInteDialog *pAddInte;

    bool isSave;
    QString getUserName();
    QString getMachineName();
    QString getIpAdress();
};

#endif // MAINWINDOW_H
