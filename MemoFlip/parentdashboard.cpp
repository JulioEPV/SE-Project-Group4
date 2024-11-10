#include "parentdashboard.h"
#include "ui_parentdashboard.h"

ParentDashboard::ParentDashboard(const QString &userType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParentDashboard)
{
    ui->setupUi(this);

    // Set the window title based on the user type
    setWindowTitle(userType + " Dashboard");
}

ParentDashboard::~ParentDashboard()
{
    delete ui;
}
