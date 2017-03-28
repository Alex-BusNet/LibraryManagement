#include "edituser.h"
#include "ui_edituser.h"

editUser::editUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editUser)
{
    ui->setupUi(this);
}

editUser::~editUser()
{
    delete ui;
}
