#include "studentdashboard.h"
#include "ui_studentdashboard.h"
#include "gamewindow.h"

StudentDashboard::StudentDashboard(const QString &userType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentDashboard),
    userType(userType)
{
    ui->setupUi(this);
    setWindowTitle("Student Dashboard");

    // Connect the Play Game button to open GameWindow
    //connect(ui->playGameButton, &QPushButton::clicked, this, &StudentDashboard::on_playGameButton_clicked);
}

StudentDashboard::~StudentDashboard()
{
    delete ui;
}

void StudentDashboard::on_playGameButton_clicked()
{
    // Create and show GameWindow
    GameWindow *gameWindow = new GameWindow(this);
    //gameWindow->setModal(false); // Non-modal, allows multiple windows
    gameWindow->show();
    gameWindow->setModal(true);
}
