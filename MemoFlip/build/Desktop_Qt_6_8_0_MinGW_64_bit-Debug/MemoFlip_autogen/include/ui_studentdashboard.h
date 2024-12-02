/********************************************************************************
** Form generated from reading UI file 'studentdashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENTDASHBOARD_H
#define UI_STUDENTDASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StudentDashboard
{
public:
    QPushButton *playGameButton;
    QLabel *Welcome;
    QLabel *nintendo;

    void setupUi(QWidget *StudentDashboard)
    {
        if (StudentDashboard->objectName().isEmpty())
            StudentDashboard->setObjectName("StudentDashboard");
        StudentDashboard->resize(400, 300);
        playGameButton = new QPushButton(StudentDashboard);
        playGameButton->setObjectName("playGameButton");
        playGameButton->setGeometry(QRect(140, 130, 91, 31));
        Welcome = new QLabel(StudentDashboard);
        Welcome->setObjectName("Welcome");
        Welcome->setGeometry(QRect(50, 30, 251, 81));
        nintendo = new QLabel(StudentDashboard);
        nintendo->setObjectName("nintendo");
        nintendo->setGeometry(QRect(60, 170, 341, 111));

        retranslateUi(StudentDashboard);

        QMetaObject::connectSlotsByName(StudentDashboard);
    } // setupUi

    void retranslateUi(QWidget *StudentDashboard)
    {
        StudentDashboard->setWindowTitle(QCoreApplication::translate("StudentDashboard", "Form", nullptr));
        playGameButton->setText(QCoreApplication::translate("StudentDashboard", "Play Game", nullptr));
        Welcome->setText(QString());
        nintendo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StudentDashboard: public Ui_StudentDashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTDASHBOARD_H
