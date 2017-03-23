#include "addnewuser.h"
#include "ui_addnewuser.h"

addNewUser::addNewUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewUser)
{
    ui->setupUi(this);
}

addNewUser::~addNewUser()
{
    delete ui;
}
