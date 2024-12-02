#include "studentdashboard.h"
#include "ui_studentdashboard.h"
#include "gamewindow.h"
#include <QPixmap>

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

    // Welcome
    QPixmap pix3("../../images/(36)welcome.jpg");
    int w3 = ui ->Welcome->width();
    int h3 = ui ->Welcome->height();
    ui->Welcome->setPixmap(pix3.scaled(w3,h3,Qt::KeepAspectRatio));

    // Nintendo
    QPixmap pix4("../../images/(37)nintendo.jpg");
    int w4 = ui ->nintendo->width();
    int h4 = ui ->nintendo->height();
    ui->nintendo->setPixmap(pix4.scaled(w4,h4,Qt::KeepAspectRatio));
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
