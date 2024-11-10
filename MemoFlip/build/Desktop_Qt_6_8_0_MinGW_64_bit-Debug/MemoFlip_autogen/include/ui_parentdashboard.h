/********************************************************************************
** Form generated from reading UI file 'parentdashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARENTDASHBOARD_H
#define UI_PARENTDASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParentDashboard
{
public:

    void setupUi(QWidget *ParentDashboard)
    {
        if (ParentDashboard->objectName().isEmpty())
            ParentDashboard->setObjectName("ParentDashboard");
        ParentDashboard->resize(400, 300);

        retranslateUi(ParentDashboard);

        QMetaObject::connectSlotsByName(ParentDashboard);
    } // setupUi

    void retranslateUi(QWidget *ParentDashboard)
    {
        ParentDashboard->setWindowTitle(QCoreApplication::translate("ParentDashboard", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParentDashboard: public Ui_ParentDashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARENTDASHBOARD_H
