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
    explicit editUser(QWidget *parent = 0, QString name = " ", QString username = " ", QString pass = " ", int cardnumber = 0, QString address = " ", QString phonenumber = " ", bool newUser = true);
    ~editUser();

private slots:
    void on_buttonBox_accepted();

    void on_checkBox_toggled(bool checked);

private:
    Ui::editUser *ui;
    bool newUser;
};

#endif // EDITUSER_H
