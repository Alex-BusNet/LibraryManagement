#include "assistantwindow.h"
#include "ui_assistantwindow.h"
#include "addnewuser.h"

assistantWindow::assistantWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::assistantWindow)
{
    ui->setupUi(this);
}

assistantWindow::~assistantWindow()
{
    delete ui;
}

void assistantWindow::on_pushButton_2_clicked()
{
    static addNewUser* userManagement = new addNewUser;
    userManagement->exec();
}
