#include "studentdashboard.h"
#include "ui_studentdashboard.h"

StudentDashboard::StudentDashboard(const QString &userType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentDashboard)
{
    ui->setupUi(this);

    // Set the window title based on the user type
    setWindowTitle(userType + " Dashboard");
}

StudentDashboard::~StudentDashboard()
{
    delete ui;
}
