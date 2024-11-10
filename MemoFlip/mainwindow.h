#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();   // This is for login button's click event
    void handleLogin();              // Declare handleLogin function
    void on_lineEdit_inputRejected();

private:
    Ui::MainWindow *ui;

    void showProfessorDashboard(const QString &userType);
    void showStudentDashboard(const QString &userType);
    void showParentDashboard(const QString &userType);
};

#endif // MAINWINDOW_H
