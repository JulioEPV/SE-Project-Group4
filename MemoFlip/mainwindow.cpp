#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "professordashboard.h"
#include "studentdashboard.h"
#include "parentdashboard.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("MemoFlip");

    // Initialize the database connection
    if (!initializeDatabase()) {
        QMessageBox::critical(this, "Database Error", "Unable to open the database.");
        return;  // Prevent further execution if database connection fails
    }

    // Populate the user type dropdown
    ui->userTypeComboBox->addItems({"Professor", "Student", "Parent"});

    // Connect the login button to the login function
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::initializeDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../../database/MemoFlipDatabase.db");  // Ensure this path is correct

    if (!db.open()) {
        qDebug() << "Error: Unable to open the database!" << db.lastError().text();
        return false;
    }

    qDebug() << "Database connection established.";

    return true;
}

void MainWindow::on_loginButton_clicked()
{
    handleLogin();
}

void MainWindow::handleLogin()
{
    QString userType = ui->userTypeComboBox->currentText();
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    // Print the entered values
    qDebug() << "Entered User Type: " << userType;
    qDebug() << "Entered Username: " << username;
    qDebug() << "Entered Password: " << password;

    // Prepare the query with direct value insertion
    QSqlQuery query;
    QString queryString = QString("SELECT * FROM users WHERE userType = '%1' AND username = '%2' AND password = '%3'")
                              .arg(userType).arg(username).arg(password);

    qDebug() << "Prepared Query: " << queryString;

    // Execute the query
    if (query.exec(queryString) && query.next()) {
        // Credentials are valid
        qDebug() << "Login successful!";
        if (userType == "Professor") {
            showProfessorDashboard(userType);
        } else if (userType == "Student") {
            showStudentDashboard(userType);
        } else if (userType == "Parent") {
            showParentDashboard(userType);
        }
    } else {
        // If query fails, print the error
        qDebug() << "Error executing query: " << query.lastError().text();
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}

void MainWindow::showProfessorDashboard(const QString &userType)
{
    this->hide();
    // Pass the QSqlDatabase reference to the ProfessorDashboard
    ProfessorDashboard *professorDashboard = new ProfessorDashboard(db, userType);
    connect(professorDashboard, &QDialog::finished, this, [=]() {
        this->show();
        delete professorDashboard;
    });
    professorDashboard->exec();
}


void MainWindow::showStudentDashboard(const QString &userType)
{
    this->hide();
    StudentDashboard *studentDashboard = new StudentDashboard(userType);
    connect(studentDashboard, &QDialog::finished, this, [=]() {
        this->show();
        delete studentDashboard;
    });
    studentDashboard->exec();
}

void MainWindow::showParentDashboard(const QString &userType)
{
    this->hide();
    ParentDashboard *parentDashboard = new ParentDashboard(userType);
    connect(parentDashboard, &QDialog::finished, this, [=]() {
        this->show();
        delete parentDashboard;
    });
    parentDashboard->exec();
}

void MainWindow::on_lineEdit_inputRejected()
{
    //
}
