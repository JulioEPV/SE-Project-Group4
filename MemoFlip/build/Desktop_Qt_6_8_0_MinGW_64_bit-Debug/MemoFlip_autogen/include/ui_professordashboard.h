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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProfessorDashboard
{
public:
    QPushButton *selectImageButton;
    QPushButton *addCardButton;
    QLabel *imagePreviewLabel;
    QLineEdit *conceptLineEdit;
    QLabel *professor;

    void setupUi(QWidget *ProfessorDashboard)
    {
        if (ProfessorDashboard->objectName().isEmpty())
            ProfessorDashboard->setObjectName("ProfessorDashboard");
        ProfessorDashboard->resize(530, 389);
        selectImageButton = new QPushButton(ProfessorDashboard);
        selectImageButton->setObjectName("selectImageButton");
        selectImageButton->setGeometry(QRect(160, 80, 80, 24));
        addCardButton = new QPushButton(ProfessorDashboard);
        addCardButton->setObjectName("addCardButton");
        addCardButton->setGeometry(QRect(290, 80, 80, 24));
        imagePreviewLabel = new QLabel(ProfessorDashboard);
        imagePreviewLabel->setObjectName("imagePreviewLabel");
        imagePreviewLabel->setGeometry(QRect(150, 120, 231, 171));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imagePreviewLabel->sizePolicy().hasHeightForWidth());
        imagePreviewLabel->setSizePolicy(sizePolicy);
        conceptLineEdit = new QLineEdit(ProfessorDashboard);
        conceptLineEdit->setObjectName("conceptLineEdit");
        conceptLineEdit->setGeometry(QRect(160, 40, 211, 24));
        professor = new QLabel(ProfessorDashboard);
        professor->setObjectName("professor");
        professor->setGeometry(QRect(370, 120, 151, 111));

        retranslateUi(ProfessorDashboard);

        QMetaObject::connectSlotsByName(ProfessorDashboard);
    } // setupUi

    void retranslateUi(QWidget *ProfessorDashboard)
    {
        ProfessorDashboard->setWindowTitle(QCoreApplication::translate("ProfessorDashboard", "Form", nullptr));
        selectImageButton->setText(QCoreApplication::translate("ProfessorDashboard", "Select Image", nullptr));
        addCardButton->setText(QCoreApplication::translate("ProfessorDashboard", "Add Card", nullptr));
        imagePreviewLabel->setText(QString());
        conceptLineEdit->setText(QCoreApplication::translate("ProfessorDashboard", "Enter Concept", nullptr));
        professor->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ProfessorDashboard: public Ui_ProfessorDashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFESSORDASHBOARD_H
