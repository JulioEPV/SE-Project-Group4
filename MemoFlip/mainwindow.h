#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>  // Include QSqlDatabase to manage the database

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadImageToLabel();

private slots:
    void on_loginButton_clicked();   // This is for login button's click event
    void handleLogin();              // Declare handleLogin function
    void on_lineEdit_inputRejected();

private:
    Ui::MainWindow *ui;

    void showProfessorDashboard(const QString &userType);
    void showStudentDashboard(const QString &userType);
    void showParentDashboard(const QString &userType);

    // Declaration for the database initialization function
    bool initializeDatabase();

    QSqlDatabase db;  // Declare a member to store the QSqlDatabase object
};

#endif // MAINWINDOW_H
