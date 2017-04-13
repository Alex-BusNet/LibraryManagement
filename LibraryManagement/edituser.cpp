#include "edituser.h"
#include "librarydb.h"
#include "staff.h"
#include "ui_edituser.h"

editUser::editUser(QWidget *parent, QString name, QString username, int cardnumber, QString address, QString phonenumber) :
    QDialog(parent),
    ui(new Ui::editUser)
{
    ui->setupUi(this);
    ui->nameLE->setText(name);
    ui->usernameLE->setText(username);
    ui->cardNumberLE->setText(QString::number(cardnumber));
    ui->addressLE->setText(address);
    ui->phoneLE->setText(phonenumber);
}

editUser::~editUser()
{
    delete ui;
}

void editUser::on_buttonBox_accepted()
{
    if(ui->staffCB->isChecked())
    {
        Staff *s = new Staff(ui->nameLE->text(),
                             ui->usernameLE->text(),
                             ui->cardNumberLE->text().toInt(),
                             ui->addressLE->text(),
                             ui->phoneLE->text());

        /// Add Update function
    }
    else
    {
        User *u = new User(ui->nameLE->text(),
                           ui->usernameLE->text(),
                           ui->cardNumberLE->text().toInt(),
                           ui->addressLE->text(),
                           ui->phoneLE->text());

        /// Add Update function
    }
}
