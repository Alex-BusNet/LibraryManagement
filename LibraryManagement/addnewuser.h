#ifndef ADDNEWUSER_H
#define ADDNEWUSER_H

#include <QDialog>

namespace Ui {
class addNewUser;
}

class addNewUser : public QDialog
{
    Q_OBJECT

public:
    explicit addNewUser(QWidget *parent = 0);
    ~addNewUser();

private:
    Ui::addNewUser *ui;
};

#endif // ADDNEWUSER_H
