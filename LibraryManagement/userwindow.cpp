#include "userwindow.h"
#include "ui_userwindow.h"

userWindow::userWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userWindow)
{
    ui->setupUi(this);
//    ui->tableWidget->
}

userWindow::~userWindow()
{
    delete ui;
}

void userWindow::on_tableWidget_2_itemClicked(QTableWidgetItem *item)
{
//    ui->tableWidget_2->
}
