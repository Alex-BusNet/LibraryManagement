#include "useroptions.h"
#include "ui_useroptions.h"
#include "librarydb.h"

#include <QDialog>

UserOptions::UserOptions(QWidget *parent, int userLevel) :
    QWidget(parent),
    ui(new Ui::UserOptions)
{
    ui->setupUi(this);
    int row = 0;
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(5662);

    QStringList headers = {"Title", "Author", "ISBN", "Copies Available", "Check-out period", "Publisher" , "Year Published"};

    ui->tableWidget->setHorizontalHeaderLabels(headers);

    int i = 0;
    this->setLayout(ui->MainLayout);

    foreach(Book* b, LibraryDB::instance()->GetAllBooks())
    {
        if(i == 0) { i++ ; continue; }
        else if(i == 5662) { break; }
        else if(b->ISBN == 0) { continue; }
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
        ui->reservedListButton->setVisible(false);
        ui->checkedOutListButton->setVisible(false);
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

        ui->editUserButton->setEnabled(false);
    }
    QStringList searchParams = {"Title", "Author", "ISBN"};
    ui->searchType->addItems(searchParams);
    ui->searchType->setCurrentIndex(0);

    activeUserLevel = userLevel;
    LibraryDB::instance()->LoadSecondaryData();
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

void UserOptions::on_searchButton_clicked()
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
        if(b == LibraryDB::instance()->GetBookAt(0)) { continue; }

        if(row == 5662) { break; }
        else if(b->ISBN == 0) { continue; }

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

void UserOptions::on_reservedListButton_clicked()
{
    QDialog *reservedDisplay = new QDialog();
    QTableWidget *tw = new QTableWidget();
    tw->setColumnCount(4);

    QStringList twheader = {"User Number", "ISBN", "Pickup Date" , "Needs Reminder"};
    tw->setHorizontalHeaderLabels(twheader);
    tw->setSortingEnabled(true);

    QVector<BookReciept*> reservationList = LibraryDB::instance()->GetAllReservations();
    int row = 0;
    QTableWidgetItem* userNo;
    QTableWidgetItem* isbn;
    QTableWidgetItem* duedate;
    QTableWidgetItem* needsreminder;

    foreach(BookReciept *br, reservationList)
    {
        userNo = new QTableWidgetItem(QString(br->userNo));
        isbn = new QTableWidgetItem(QString::number(br->ISBN));
        duedate = new QTableWidgetItem(br->dateDue.toString());
        needsreminder = new QTableWidgetItem(br->needsReminder);

        tw->setItem(row, 0, userNo);
        tw->setItem(row, 1, isbn);
        tw->setItem(row, 2, duedate);
        tw->setItem(row, 3, needsreminder);

        row++;

    }

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tw);
    reservedDisplay->setLayout(layout);

    reservedDisplay->show();
}

void UserOptions::on_checkedOutListButton_clicked()
{
    QDialog *checkedoutDisplay = new QDialog();
    QTableWidget *tw = new QTableWidget();
    tw->setColumnCount(4);

    QStringList twheader = {"User Number", "ISBN", "Due Date" , "Needs Reminder"};
    tw->setHorizontalHeaderLabels(twheader);
    tw->setSortingEnabled(true);

    QVector<BookReciept*> checkoutList = LibraryDB::instance()->GetAllCheckedOutBooks();
    int row = 0;
    QTableWidgetItem* userNo;
    QTableWidgetItem* isbn;
    QTableWidgetItem* duedate;
    QTableWidgetItem* needsreminder;
    qDebug() << checkoutList.size();
    tw->setRowCount(checkoutList.size());

    foreach(BookReciept *br, checkoutList)
    {
        userNo = new QTableWidgetItem(QString::number(br->userNo));
        isbn = new QTableWidgetItem(QString::number(br->ISBN));
        duedate = new QTableWidgetItem(br->dateDue.toString());
        needsreminder = new QTableWidgetItem(br->needsReminder);

        tw->setItem(row, 0, userNo);
        tw->setItem(row, 1, isbn);
        tw->setItem(row, 2, duedate);
        tw->setItem(row, 3, needsreminder);

        row++;
    }

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tw);
    checkedoutDisplay->setLayout(layout);
    checkedoutDisplay->setWindowTitle("Checked out Books");
    checkedoutDisplay->show();
}

void UserOptions::on_editUserButton_clicked()
{
    if(eu != NULL)
    {
        delete eu;
    }

//    eu = new editUser(0, ui->userInfoTable->currentRow());
    //Load user info to dialog
    eu->show();
}

void UserOptions::on_userInfoTable_itemActivated(QTableWidgetItem *item)
{
    ui->editUserButton->setEnabled(true);
}

void UserOptions::on_userInfoTable_cellDoubleClicked(int row, int column)
{
    qDebug() << "Edit User diag";

    //Show Edit user dialog
}

void UserOptions::on_userInfoTable_cellChanged(int row, int column)
{

}

void UserOptions::on_tableWidget_itemPressed(QTableWidgetItem *item)
{
    qDebug() << "Item at" << item->column() << item->row() << "pressed";
    ui->tableWidget->selectRow(item->row());
}

void UserOptions::on_borrowBookButton_clicked()
{
    LibraryDB::instance()->CheckOutBook(LibraryDB::instance()->GetUser(ui->userIdLineEdit->text().toInt()),
                                        LibraryDB::instance()->GetBook(ui->isbnLineEdit->text().toLongLong()),
                                        false,false);
}

void UserOptions::on_returnBookButton_clicked()
{
    LibraryDB::instance()->ReturnBook(ui->isbnLineEdit->text().toLongLong());
}

void UserOptions::on_reserveBookButton_clicked()
{
    LibraryDB::instance()->CheckOutBook(LibraryDB::instance()->GetUser(LibraryDB::instance()->GetActiveUser()),
                                        LibraryDB::instance()->GetBook(ui->tableWidget->currentItem()->text().toLongLong()),
                                        false,true);
}
