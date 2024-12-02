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
#include <QPixmap>

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
    loadImageToLabel();

    // Title
    QPixmap pix("../../images/(34)Title.jpg");
    int w = ui ->title->width();
     int h = ui ->title->height();
    ui->title->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

     // board
     QPixmap pix2("../../images/(35)iboard.jpg");
     int w2 = ui ->iboard->width();
     int h2 = ui ->iboard->height();
     ui->iboard->setPixmap(pix2.scaled(w2,h2,Qt::KeepAspectRatio));
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

    // Print the entered values for debugging
    qDebug() << "Entered User Type: " << userType;
    qDebug() << "Entered Username: " << username;
    qDebug() << "Entered Password: " << password;

    // Prepare the query using parameterized statements to avoid SQL injection
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE userType = :userType AND username = :username AND password = :password");
    query.bindValue(":userType", userType);
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    qDebug() << "Prepared Query: " << query.executedQuery();

    // Execute the query
    if (query.exec() && query.next()) {
        // Credentials are valid
        qDebug() << "Login successful!";
        if (userType == "Professor") {
            showProfessorDashboard(userType);
        } else if (userType == "Student") {
            showStudentDashboard(username); // Pass the actual username
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

void MainWindow::showStudentDashboard(const QString &username)
{
    this->hide();
    QString userType = "Student";  // You can get this value from the login or pass it along
    // Pass the username to the StudentDashboard
    StudentDashboard *studentDashboard = new StudentDashboard(userType, username);
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

void MainWindow::loadImageToLabel() {
    QString imagePath = "./../images/(33)Title.jpg";
    QPixmap image(imagePath);
    ui->label_4->setPixmap(image);
    ui->label_4->setScaledContents(true);
}


void MainWindow::on_lineEdit_inputRejected()
{
    // Handle input rejection if necessary
}


