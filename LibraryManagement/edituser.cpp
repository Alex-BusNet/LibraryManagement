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
    ui->passwordLE->setEchoMode(QLineEdit::Password);
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

    if(Manager::instanceof(LibraryDB::instance()->GetUser(username)))
    {
        ui->managerRB->setChecked(true);
    }
    else if(Staff::instanceof(LibraryDB::instance()->GetUser(username)))
    {
        ui->staffRB->setChecked(true);
    }
    else
    {
        ui->userRB->setChecked(true);
    }

    this->newUser = newUser;
}

editUser::~editUser()
{
    delete ui;
}

void editUser::on_buttonBox_accepted()
{
    if(ui->managerRB->isChecked())
    {
        qDebug() << "Manager";
        Manager *m = new Manager(ui->nameLE->text(),
                             ui->addressLE->text(),
                             ui->phoneLE->text(),
                             ui->usernameLE->text());

        if(newUser)
        {
            LibraryDB::instance()->AddUser(m, ui->passwordLE->text());
            LibraryDB::instance()->AddStaff(m);
        }
        else
        {
            m->SetCardNumber(ui->cardNumberLE->text().toInt());
            LibraryDB::instance()->UpdateUser(m->GetCardNumber(), static_cast<Manager*>(m), true);
        }
    }
    else if(ui->staffRB->isChecked())
    {
        qDebug() << "Staff";
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
            LibraryDB::instance()->UpdateUser(s->GetCardNumber(), static_cast<Staff*>(s), true);
        }
    }
    else
    {
        qDebug() << "User";
        User *u = new User(ui->nameLE->text(),
                           ui->addressLE->text(),
                           ui->phoneLE->text(),
                           ui->usernameLE->text());

        if(newUser)
        {
            LibraryDB::instance()->AddUser(u, ui->passwordLE->text());
        }
        else
        {
            u->SetCardNumber(ui->cardNumberLE->text().toInt());
            LibraryDB::instance()->UpdateUser(u->GetCardNumber(), u, false);
        }
    }
}

void editUser::on_checkBox_toggled(bool checked)
{
    if(checked)
    {
        ui->passwordLE->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->passwordLE->setEchoMode(QLineEdit::Password);
    }
}
