#include "studentdashboard.h"
#include "ui_studentdashboard.h"
#include "gamewindow.h"

StudentDashboard::StudentDashboard(const QString &userType, const QString &username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentDashboard),
    userType(userType),
    username(username)
{
    ui->setupUi(this);
    setWindowTitle("Student Dashboard");

    gameWindow = nullptr; // Initialize gameWindow to nullptr

    // Connect the Play Game button to open GameWindow
    connect(ui->playGameButton, &QPushButton::clicked, this, &StudentDashboard::on_playGameButton_clicked);
}

StudentDashboard::~StudentDashboard()
{
    delete ui;
    if (gameWindow) {
        delete gameWindow;
    }
}

void StudentDashboard::on_playGameButton_clicked()
{
    // Only create a new GameWindow if one isn't already open
    if (!gameWindow) {
        gameWindow = new GameWindow(username, this);

        // Connect the restart signal to handle restarts
        bool connected = connect(gameWindow, &GameWindow::restartRequested, this, &StudentDashboard::onRestartRequested);
        qDebug() << "Connection successful:" << connected;

        // Show the GameWindow (non-modal to avoid blocking)
        gameWindow->show();
    }
}

void StudentDashboard::onRestartRequested() {
    qDebug() << "Restart requested!";

    // Close and delete the existing modal GameWindow
    if (gameWindow) {
        gameWindow->close();
        delete gameWindow;
        gameWindow = nullptr; // Reset the pointer
    }

    // Create a new GameWindow instance and show it
    gameWindow = new GameWindow(username, this);
    connect(gameWindow, &GameWindow::restartRequested, this, &StudentDashboard::onRestartRequested);

    // Show the new instance of the GameWindow (non-modal to avoid blocking)
    gameWindow->show();
}
