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

    QStringList headers = {"Title", "Author", "ISBN", "Copies Available", "Check-out period", "Publisher" , "Year Published"};

    ui->tableWidget->setSortingEnabled(false);
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    int i = 0;
    this->setLayout(ui->MainLayout);

    foreach(Book* b, LibraryDB::instance()->GetAllBooks())
    {
        if(i == 0) { i++ ; continue; }
        else if(i == 5662) { break; }
        else { i++; }

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

    for(int j = 0; j < 7; j++)
    {
        ui->tableWidget->setColumnWidth(j, ui->tableWidget->width() / 7);
    }

    if(userLevel == 0)
    {
        ui->addUserButton->setVisible(false);
        ui->removeUserButton->setVisible(false);
        ui->editUserButton->setVisible(false);
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
    else if(userLevel == 1)
    {
        ui->addUserButton->setVisible(false);
        ui->removeUserButton->setVisible(false);
        ui->editUserButton->setVisible(false);
        ui->userInfoTable->setVisible(false);
        ui->userTableLabel->setVisible(false);
    }
    else if(userLevel == 2)
    {
        int userRow = 0;
        foreach(UserBase* ub, LibraryDB::instance()->GetAllUsers())
        {
            QStringList uheader = {"ID", "Name", "Access Level" };
            ui->userInfoTable->setColumnCount(3);
            ui->userInfoTable->setRowCount(LibraryDB::instance()->GetNumberOfUsers());
            ui->userInfoTable->setHorizontalHeaderLabels(uheader);

            userID = new QTableWidgetItem(QString::number(ub->GetCardNumber()));
            userName = new QTableWidgetItem(ub->GetName());
            userAccess = new QTableWidgetItem(QString::number(LibraryDB::instance()->Authenticate(ub)));

            ui->userInfoTable->setItem(userRow, 0, userID);
            ui->userInfoTable->setItem(userRow, 1, userName);
            ui->userInfoTable->setItem(userRow, 2, userAccess);

            userRow++;
        }
    }
    QStringList searchParams = {"Title", "Author", "ISBN"};
    ui->searchType->addItems(searchParams);
    ui->searchType->setCurrentIndex(0);

    activeUserLevel = userLevel;
}

void UserOptions::paintEvent(QPaintEvent *e)
{
    for(int j = 0; j < 7; j++)
    {
        ui->tableWidget->setColumnWidth(j, ui->tableWidget->width() / 7);
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
}

void UserOptions::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    if(activeUserLevel > 0)
    {
        //Open Edit book Dialog
    }
}

void UserOptions::on_pushButton_clicked()
{
    int search = ui->searchType->currentIndex();
    QVector<Book*> results;

    if(ui->searchBar->text().isEmpty())
        search = 3;

    switch(search)
    {
    case 0: // Title
        results = LibraryDB::instance()->GetBooks(ui->searchBar->text());
        break;
    case 1: // Author
        results = LibraryDB::instance()->GetBooks("", ui->searchBar->text());
        break;
    case 2: // ISBN
        results.push_back(LibraryDB::instance()->GetBook(ui->searchBar->text().toInt()));
        break;
    default: // Get all books
        results = LibraryDB::instance()->GetAllBooks();
        break;
    }

    int row = 0;
    ui->tableWidget->setRowCount(results.size());
    foreach(Book* b, results)
    {
        // Skip book if it is the first book (Empty book reference)
        if(b == LibraryDB::instance()->GetAllBooks().at(0)) { continue; }

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
