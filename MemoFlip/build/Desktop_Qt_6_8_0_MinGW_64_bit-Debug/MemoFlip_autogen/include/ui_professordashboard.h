/********************************************************************************
** Form generated from reading UI file 'professordashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFESSORDASHBOARD_H
#define UI_PROFESSORDASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProfessorDashboard
{
public:

    void setupUi(QWidget *ProfessorDashboard)
    {
        if (ProfessorDashboard->objectName().isEmpty())
            ProfessorDashboard->setObjectName("ProfessorDashboard");
        ProfessorDashboard->resize(400, 300);

        retranslateUi(ProfessorDashboard);

        QMetaObject::connectSlotsByName(ProfessorDashboard);
    } // setupUi

    void retranslateUi(QWidget *ProfessorDashboard)
    {
        ProfessorDashboard->setWindowTitle(QCoreApplication::translate("ProfessorDashboard", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProfessorDashboard: public Ui_ProfessorDashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFESSORDASHBOARD_H
