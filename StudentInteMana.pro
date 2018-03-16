#-------------------------------------------------
#
# Project created by QtCreator 2018-03-02T18:40:16
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudentInteMana
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    student.cpp \
    interestmana.cpp \
    addstudentdialog.cpp \
    showallinfodialog.cpp \
    stuInfoDialog.cpp \
    showInteDialog.cpp \
    addInteDialog.cpp \
    addInteForStudentDialog.cpp \
    inteDetailDialog.cpp \
    addStuForInteDialog.cpp

HEADERS  += mainwindow.h \
    student.h \
    interestmana.h \
    addstudentdialog.h \
    showallinfodialog.h \
    stuInfoDialog.h \
    showInteDialog.h \
    addInteDialog.h \
    addInteForStudentDialog.h \
    inteDetailDialog.h \
    addStuForInteDialog.h

FORMS    += mainwindow.ui \
    addstudentdialog.ui \
    showallinfodialog.ui \
    stuInfoDialog.ui \
    showInteDialog.ui \
    addInteDialog.ui \
    addInteForStudentDialog.ui \
    inteDetailDialog.ui \
    addStuForInteDialog.ui

RESOURCES += \
    studentintemanapicture.qrc

OTHER_FILES+=myapp.rc
RC_FILE+=myapp.rc
