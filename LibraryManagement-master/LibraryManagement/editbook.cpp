#include "editbook.h"
#include "ui_editbook.h"

editBook::editBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editBook)
{
    ui->setupUi(this);
}

editBook::~editBook()
{
    delete ui;
}
