#include "assistant.h"
#include "librarydb.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Assistant *a = new Assistant("Alex", 0000001, "1294 Peachtree Ave.", 5555555555, "arport");
    User *b = new User("Sparta", 000002, "12345 Peachtree Ave", 4444444444, "sparta");

    LibraryDB::instance()->AddUser(a, QString("sparta"));
    LibraryDB::instance()->AddUser(b, QString("sparta2"));
    LibraryDB::instance()->AddStaff(a);

    qDebug() << a->GetUsername() << "Instanceof of user" << User::instanceof(b);
    qDebug() << b->GetUsername() << "Instanceof of user" << User::instanceof(a);
//    LibraryDB::instance()->Authenticate(a);
//    LibraryDB::instance()->Authenticate(b);
}

MainWindow::~MainWindow()
{
    delete ui;
}
