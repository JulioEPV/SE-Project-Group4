#ifndef PROFESSORDASHBOARD_H
#define PROFESSORDASHBOARD_H

#include <QDialog>
#include <QString>
#include <QSqlDatabase>

namespace Ui {
class ProfessorDashboard;
}

class ProfessorDashboard : public QDialog
{
    Q_OBJECT

public:
    // Constructor that accepts a QSqlDatabase reference
    explicit ProfessorDashboard(QSqlDatabase &db, const QString &userType, QWidget *parent = nullptr);
    ~ProfessorDashboard();

private slots:
    void on_selectImageButton_clicked();
    void on_addCardButton_clicked();

private:
    Ui::ProfessorDashboard *ui;
    QSqlDatabase database;  // Store the database reference
    QString selectedImagePath;  // Store the selected image path
};

#endif // PROFESSORDASHBOARD_H
