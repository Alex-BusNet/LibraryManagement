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

    Manager *a = new Manager("Alex", "1294 Peachtree Ave.", 5555555555, "arport");
    User *b = new User("Sparta", "12345 Peachtree Ave", 4444444444, "sparta");

    LibraryDB::instance()->AddUser(a, QString("sparta"));
    LibraryDB::instance()->AddUser(b, QString("sparta2"));
    LibraryDB::instance()->AddStaff(a);

//    qDebug() << "Log in successful for" << a->GetName() <<  LibraryDB::instance()->LogIn(a->GetUsername(), "sparta");
//    qDebug() << "Log in successful for" << b->GetName() <<  LibraryDB::instance()->LogIn(b->GetUsername(), "sparta2");
//    qDebug() << "Log in successful for" << "John" <<  LibraryDB::instance()->LogIn("johnDoe", "IAmTheBest");

//    LibraryDB::instance()->Authenticate(a);
//    LibraryDB::instance()->Authenticate(b);

//    Book bo{"C++ The Complete Reference", "Herbert Shildt", 1234567890, QVector<int>{-1,-1,-1}, true};
//    if(a->CanCheckOutBook())
//        a->CheckOutBook(bo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()
{
    QString un = ui->username->text(), pw = ui->password->text();
    if(LibraryDB::instance()->LogIn(un, pw))
    {
        UserBase* u = LibraryDB::instance()->GetUser(un);
        int loadUI = LibraryDB::instance()->Authenticate(u);
        qDebug() << "User has level access:" << loadUI;

        //----------------------------
        //Development testing
        QVector<UserBase*> users = LibraryDB::instance()->GetAllUsers();
        foreach(UserBase* ub, users)
        {
            qDebug() << ub->GetName() << ub->GetUsername() << ub->GetCardNumber();
        }

        //-----------------------------

    }
    else
    {
        ui->badLogin->setVisible(true);
    }
}
