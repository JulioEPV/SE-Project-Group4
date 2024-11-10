#ifndef PARENTDASHBOARD_H
#define PARENTDASHBOARD_H

#include <QDialog>
#include <QString>

namespace Ui {
class ParentDashboard;
}

class ParentDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit ParentDashboard(const QString &userType, QWidget *parent = nullptr);
    ~ParentDashboard();

private:
    Ui::ParentDashboard *ui;
};

#endif // PARENTDASHBOARD_H
