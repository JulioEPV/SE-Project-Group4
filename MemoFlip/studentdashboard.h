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

private:
    Ui::StudentDashboard *ui;
};

#endif // STUDENTDASHBOARD_H
