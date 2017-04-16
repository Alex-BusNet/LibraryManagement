#include "librarydb.h"
#include "datatypes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "manager.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->badLogin->setVisible(false);
    ui->password->setEchoMode(QLineEdit::Password);
    ui->username->setFocus();
    uo = NULL;

    LibraryDB::instance()->ParseDBJson();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()
{
    QString un = ui->username->text(), pw = ui->password->text();

    int loadUI = LibraryDB::instance()->LogIn(un, pw);
    if(loadUI >= 0)
    {
        if(uo != NULL)
        {
            delete uo;
        }

        uo = new UserOptions(0, loadUI);
        uo->show();

    }
    else
    {
        ui->badLogin->setVisible(true);
    }
}

void MainWindow::on_password_returnPressed()
{
    on_login_clicked();
}
