#ifndef PROFESSORDASHBOARD_H
#define PROFESSORDASHBOARD_H

#include <QDialog>
#include <QString>

namespace Ui {
class ProfessorDashboard;
}

class ProfessorDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit ProfessorDashboard(const QString &userType, QWidget *parent = nullptr);
    ~ProfessorDashboard();

private:
    Ui::ProfessorDashboard *ui;
};

#endif // PROFESSORDASHBOARD_H
