/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *shuffleButton;
    QPushButton *exitButton;
    QPushButton *restartButton;

    void setupUi(QWidget *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName("GameWindow");
        GameWindow->resize(746, 726);
        horizontalLayoutWidget = new QWidget(GameWindow);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 640, 741, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        shuffleButton = new QPushButton(horizontalLayoutWidget);
        shuffleButton->setObjectName("shuffleButton");
        shuffleButton->setMaximumSize(QSize(100, 25));

        horizontalLayout->addWidget(shuffleButton);

        exitButton = new QPushButton(horizontalLayoutWidget);
        exitButton->setObjectName("exitButton");
        exitButton->setMaximumSize(QSize(100, 25));

        horizontalLayout->addWidget(exitButton);

        restartButton = new QPushButton(horizontalLayoutWidget);
        restartButton->setObjectName("restartButton");
        restartButton->setMaximumSize(QSize(100, 25));

        horizontalLayout->addWidget(restartButton);


        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QWidget *GameWindow)
    {
        GameWindow->setWindowTitle(QCoreApplication::translate("GameWindow", "Form", nullptr));
        shuffleButton->setText(QCoreApplication::translate("GameWindow", "Shuffle", nullptr));
        exitButton->setText(QCoreApplication::translate("GameWindow", "Exit", nullptr));
        restartButton->setText(QCoreApplication::translate("GameWindow", "Restart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
