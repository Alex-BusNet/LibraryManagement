#include "edituser.h"
#include "librarydb.h"
#include "staff.h"
#include "ui_edituser.h"

editUser::editUser(QWidget *parent, QString name, QString username, QString pass, int cardnumber, QString address, QString phonenumber, bool newUser) :
    QDialog(parent),
    ui(new Ui::editUser)
{
    ui->setupUi(this);
    ui->nameLE->setText(name);
    ui->usernameLE->setText(username);
    ui->passwordLE->setText(pass);

    if(newUser)
    {
        ui->label_3->setVisible(false);
        ui->cardNumberLE->setVisible(false);
    }
    else
        ui->cardNumberLE->setText(QString::number(cardnumber));

    ui->addressLE->setText(address);
    ui->phoneLE->setText(phonenumber);

    if(Staff::instanceof(LibraryDB::instance()->GetUser(username)))
    {
        ui->staffCB->setChecked(true);
    }
    else
    {
        ui->staffCB->setChecked(false);
    }

    this->newUser = newUser;
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
                             ui->addressLE->text(),
                             ui->phoneLE->text(),
                             ui->usernameLE->text());

        if(newUser)
        {
            LibraryDB::instance()->AddUser(s, ui->passwordLE->text());
            LibraryDB::instance()->AddStaff(s);
        }
        else
        {
            s->SetCardNumber(ui->cardNumberLE->text().toInt());
            LibraryDB::instance()->UpdateUser(s->GetCardNumber(), s, true);
        }
    }
    else
    {
        User *u = new User(ui->nameLE->text(),
                           ui->addressLE->text(),
                           ui->phoneLE->text(),
                           ui->usernameLE->text());

        if(newUser)
            LibraryDB::instance()->AddUser(u, ui->passwordLE->text());
        else
        {
            u->SetCardNumber(ui->cardNumberLE->text().toInt());
            LibraryDB::instance()->UpdateUser(u->GetCardNumber(), u, false);
        }
    }
}
