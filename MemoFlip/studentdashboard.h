#ifndef STUDENTDASHBOARD_H
#define STUDENTDASHBOARD_H

#include <QDialog>
#include <QString>

namespace Ui {
class StudentDashboard;
}

class StudentDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit StudentDashboard(const QString &userType, QWidget *parent = nullptr);
    ~StudentDashboard();

private slots:
    void on_playGameButton_clicked();

private:
    Ui::StudentDashboard *ui;
    QString userType;

};

#endif // STUDENTDASHBOARD_H
