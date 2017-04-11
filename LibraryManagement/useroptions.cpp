#include "useroptions.h"
#include "ui_useroptions.h"
#include "librarydb.h"

UserOptions::UserOptions(QWidget *parent, int userLevel) :
    QWidget(parent),
    ui(new Ui::UserOptions)
{
    ui->setupUi(this);
    int row = 0;
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(5662);

    QTableWidgetItem *title;
    QTableWidgetItem *author;
    QTableWidgetItem *ISBN;
    QTableWidgetItem *copies;
    QTableWidgetItem *longTerm;
    QTableWidgetItem *publisher;
    QTableWidgetItem *publishYear;

    QStringList headers = {"Title", "Author", "ISBN", "Copies Available", "Check-out period", "Publisher" , "Year Published"};

    ui->tableWidget->setSortingEnabled(false);
    QHeaderView * hv = new QHeaderView(Qt::Horizontal, ui->tableWidget);
    ui->tableWidget->setHorizontalHeader(hv);
    hv->setStretchLastSection(true);
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    int i = 0;
    this->setLayout(ui->MainLayout);

    foreach(Book* b, LibraryDB::instance()->GetAllBooks())
    {
        if(i == 0) { i++ ; continue; }

        title = new QTableWidgetItem(b->title);
        author = new QTableWidgetItem(b->author);
        ISBN = new QTableWidgetItem(QString::number(b->ISBN));
        copies = new QTableWidgetItem(QString::number(LibraryDB::instance()->GetCopiesOfBook(b->ISBN)));
        longTerm = new QTableWidgetItem((b->longTerm) ? "4 Weeks" : "1 Week");
        publisher = new QTableWidgetItem(b->publisher);
        publishYear = new QTableWidgetItem(QString::number(b->publishYear));

        ui->tableWidget->setItem(row, 0, title);
        ui->tableWidget->setItem(row, 1, author);
        ui->tableWidget->setItem(row, 2, ISBN);
        ui->tableWidget->setItem(row, 3, copies);
        ui->tableWidget->setItem(row, 4, longTerm);
        ui->tableWidget->setItem(row, 5, publisher);
        ui->tableWidget->setItem(row, 6, publishYear);

        row++;
    }

    if(userLevel == 0)
    {
        ui->addUserButton->setVisible(false);
        ui->removeUserButton->setVisible(false);
        ui->borrowBookButton->setVisible(false);
        ui->returnBookButton->setVisible(false);
        ui->userIdLabel->setVisible(false);
        ui->userIdLineEdit->setVisible(false);
        ui->isbnLabel->setVisible(false);
        ui->isbnLineEdit->setVisible(false);
        ui->userInfoTable->setVisible(false);
        ui->userTableLabel->setVisible(false);
        ui->managerSpace->changeSize(10, 10, QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    activeUserLevel = userLevel;
}

UserOptions::~UserOptions()
{
    delete ui;
}

void UserOptions::on_save_quit_button_clicked()
{
    LibraryDB::instance()->SaveData();
    this->close();
}

void UserOptions::on_save_button_clicked()
{
    LibraryDB::instance()->SaveData();
//    this->close();
}

void UserOptions::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    if(activeUserLevel > 0)
    {
        //Open Edit book Dialog
    }
}
