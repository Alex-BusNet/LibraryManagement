#include "useroptions.h"
#include "ui_useroptions.h"
#include "librarydb.h"

UserOptions::UserOptions(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserOptions)
{
    ui->setupUi(this);
    int row = 0;
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(260453);

    QTableWidgetItem *title;
    QTableWidgetItem *author;
    QTableWidgetItem *ISBN;
    QTableWidgetItem *copies;
    QTableWidgetItem *longTerm;
    QTableWidgetItem *publisher;
    QTableWidgetItem *publishYear;

    ui->tableWidget->setSortingEnabled(false);

    foreach(Book* b, LibraryDB::instance()->GetAllBooks()){

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

void UserOptions::on_book_table_doubleClicked(const QModelIndex &index)
{

}
