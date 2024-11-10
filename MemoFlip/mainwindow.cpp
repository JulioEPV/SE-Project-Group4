#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "professordashboard.h"  // Include the header of the Professor Dashboard
#include "studentdashboard.h"    // Include the header of the Student Dashboard
#include "parentdashboard.h"     // Include the header of the Parent Dashboard

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("MemoFlip");

    // Populate the user type dropdown
    ui->userTypeComboBox->addItems({"Professor", "Student", "Parent"});

    // Connect the login button to the login function
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    // Call the handleLogin function when the login button is clicked
    handleLogin();
}

void MainWindow::handleLogin()
{
    QString userType = ui->userTypeComboBox->currentText();
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    // For testing, we use hardcoded credentials for each type
    if (userType == "Professor" && username == "professor" && password == "pass") {
        // Navigate to the professor-specific part of the program
        showProfessorDashboard(userType);
    } else if (userType == "Student" && username == "student" && password == "pass") {
        // Navigate to the student-specific part of the program
        showStudentDashboard(userType);
    } else if (userType == "Parent" && username == "parent" && password == "pass") {
        // Navigate to the parent-specific part of the program
        showParentDashboard(userType);
    } else {
        // Show an error message for invalid credentials
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}

void MainWindow::showProfessorDashboard(const QString &userType)
{
    // Create the Professor Dashboard dynamically
    ProfessorDashboard *professorDashboard = new ProfessorDashboard(userType);
    professorDashboard->exec();  // Open the professor dashboard in a modal dialog

    // Optionally delete the dashboard manually after it is closed
    delete professorDashboard;
}

void MainWindow::showStudentDashboard(const QString &userType)
{
    // Create the Student Dashboard dynamically
    StudentDashboard *studentDashboard = new StudentDashboard(userType);
    studentDashboard->exec();  // Open the student dashboard in a modal dialog

    // Optionally delete the dashboard manually after it is closed
    delete studentDashboard;
}

void MainWindow::showParentDashboard(const QString &userType)
{
    // Create the Parent Dashboard dynamically
    ParentDashboard *parentDashboard = new ParentDashboard(userType);
    parentDashboard->exec();  // Open the parent dashboard in a modal dialog

    // Optionally delete the dashboard manually after it is closed
    delete parentDashboard;
}

void MainWindow::on_lineEdit_inputRejected()
{
    // Your code here (for example, showing an error message or handling input rejection)
}
