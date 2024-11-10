#include "professordashboard.h"
#include "ui_professordashboard.h"

ProfessorDashboard::ProfessorDashboard(const QString &userType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfessorDashboard)
{
    ui->setupUi(this);

    // Set the window title based on the user type
    setWindowTitle(userType + " Dashboard");
}

ProfessorDashboard::~ProfessorDashboard()
{
    delete ui;
}
