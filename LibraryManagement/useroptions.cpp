#include "useroptions.h"
#include "ui_useroptions.h"
#include "librarydb.h"

UserOptions::UserOptions(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserOptions)
{
    ui->setupUi(this);
    int row = 0;
    foreach(Book* b, LibraryDB::instance()->GetAllBooks()){

    QTableWidgetItem *title = new QTableWidgetItem(b->title);
        tableWidget->setItem(row, 0, newItem);
    QTableWidgetItem *author = new QTableWidgetItem(b->author);
        tableWidget->setItem(row, 0, newItem);
    QTableWidgetItem *ISBN = new QTableWidgetItem(b->ISBN);
        tableWidget->setItem(row, 0, newItem);
    QTableWidgetItem *copies = new QTableWidgetItem(b->copiesAvailable);
        tableWidget->setItem(row, 0, newItem);
    QTableWidgetItem *longTerm = new QTableWidgetItem(b->longTerm);
        tableWidget->setItem(row, 0, newItem);
    QTableWidgetItem *publisher = new QTableWidgetItem(b->publisher);
        tableWidget->setItem(row, 0, newItem);
    QTableWidgetItem *publishYear = new QTableWidgetItem(b->publishYear);
        tableWidget->setItem(row, 0, newItem);

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
}

void UserOptions::on_save_button_clicked()
{
    LibraryDB::instance()->SaveData();
    this->close();
}

void UserOptions::on_book_table_doubleClicked(const QModelIndex &index)
{

}
