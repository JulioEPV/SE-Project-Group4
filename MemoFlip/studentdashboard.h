#ifndef STUDENTDASHBOARD_H
#define STUDENTDASHBOARD_H

#include <QDialog>
#include <QString>
#include <QPushButton>
#include "gamewindow.h"

namespace Ui {
class StudentDashboard;
}

class StudentDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit StudentDashboard(const QString &userType, const QString &username, QWidget *parent = nullptr);
    ~StudentDashboard();

private slots:
    void on_playGameButton_clicked();
    void onRestartRequested();

private:
    Ui::StudentDashboard *ui;
    QString userType;
    GameWindow *gameWindow;
    QPushButton *playGameButton;
    QString username;

};

#endif // STUDENTDASHBOARD_H
