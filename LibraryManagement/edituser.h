#ifndef EDITUSER_H
#define EDITUSER_H

#include <QDialog>

namespace Ui {
class editUser;
}

class editUser : public QDialog
{
    Q_OBJECT

public:
    explicit editUser(QWidget *parent = 0, QString name, QString username, int cardnumber, QString address, QString phonenumber);
    ~editUser();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::editUser *ui;
};

#endif // EDITUSER_H
