#include "datatypes.h"
#include "editbook.h"
#include "ui_editbook.h"
#include "librarydb.h"

editBook::editBook(QWidget *parent, QString title, QString author, QString ISBN, int copies, QString publisher, int publishYear, bool newBook) :
    QDialog(parent),
    ui(new Ui::editBook)
{
    ui->setupUi(this);
    ui->titleLE->setText(title);
    ui->authorLE->setText(author);
    ui->isbnLE->setText(ISBN);
    ui->copiesLE->setText(QString::number(copies));
    ui->publisherLE->setText(publisher);
    ui->yopLE->setText(QString::number(publishYear));

    this->newBook = newBook;
}


editBook::~editBook()
{
    delete ui;
}

void editBook::on_buttonBox_accepted()
{
    Book *b = new Book{ui->titleLE->text(),
                    ui->authorLE->text(),
                    ui->isbnLE->text().toLongLong(),
                    QVector<int>{-1, -1, -1},
                    ui->longtermCB->isChecked(),
                    ui->publisherLE->text(),
                    ui->yopLE->text().toInt(),
                    true};

    QVector<int> copies;
    for(int i = 0; i < ui->copiesLE->text().toInt(); i++)
    {
        copies.push_back(-1);
    }

    b->copiesAvailable = copies;

    if(newBook)
        LibraryDB::instance()->AddBook(b);
    else
        LibraryDB::instance()->EditBook(b->ISBN, b);
}
