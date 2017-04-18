#include "useroptions.h"
#include "ui_useroptions.h"
#include "librarydb.h"
#include "recieptviewer.h"

#include <QDialog>
#include <QMessageBox>

UserOptions::UserOptions(QWidget *parent, int userLevel) :
    QWidget(parent),
    ui(new Ui::UserOptions)
{
    ui->setupUi(this);
    int row = 0;
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(5662);
    eu = NULL;
    eb = NULL;
    QStringList headers = {"Title", "Author", "ISBN", "Copies Available", "Check-out period", "Publisher" , "Year Published"};

    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->userInfoTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->userInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int i = 0;
    this->setLayout(ui->MainLayout);

    foreach(Book* b, LibraryDB::instance()->GetAllBooks())
    {
        if(i == 0) { i++ ; continue; }
        else if(b->ISBN.toLongLong() == 0) { continue; }
        else if(i == 5662) { break; }
        else { i++; }

        title = new QTableWidgetItem(b->title);
        author = new QTableWidgetItem(b->author);
        ISBN = new QTableWidgetItem(b->ISBN);
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
        ui->addBookButton->setVisible(false);
        ui->removeBookButton->setVisible(false);
        ui->editBookButton->setVisible(false);
        ui->frame->setVisible(false);
        ui->reminderCB->setVisible(false);
        ui->addBookButton->setVisible(false);
        ui->editBookButton->setVisible(false);
        ui->removeBookButton->setVisible(false);
        ui->managerSpace->changeSize(10, 10, QSizePolicy::Fixed, QSizePolicy::Fixed);
    }
    else if(userLevel == 1)
    {
        ui->addUserButton->setVisible(false);
        ui->removeUserButton->setVisible(false);
        ui->editUserButton->setVisible(false);
        ui->userInfoTable->setVisible(false);
        ui->userTableLabel->setVisible(false);
        ui->addBookButton->setVisible(false);
        ui->editBookButton->setVisible(false);
        ui->removeBookButton->setVisible(false);
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
        ui->removeUserButton->setEnabled(false);
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

    if(ui->tableWidget->selectedItems().isEmpty())
    {
        ui->removeBookButton->setEnabled(false);
        ui->reserveBookButton->setEnabled(false);
    }

    if(ui->userInfoTable->selectedItems().isEmpty())
    {
        ui->editUserButton->setEnabled(false);
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

void UserOptions::on_searchButton_clicked()
{
    int search = ui->searchType->currentIndex();
    QVector<Book*> results;

    if(ui->searchBar->text().isEmpty())
        search = 3;

    switch(search)
    {
    case 0: // Title
        results = LibraryDB::instance()->GetBooks(ui->searchBar->text(), LibraryDB::TITLE);
        break;
    case 1: // Author
        results = LibraryDB::instance()->GetBooks(ui->searchBar->text(), LibraryDB::AUTHOR);
        break;
    case 2: // ISBN
        results = LibraryDB::instance()->GetBooks(ui->searchBar->text(), LibraryDB::ISBN);
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
        else if(b->ISBN.toLongLong() == 0) { continue; }

        title = new QTableWidgetItem(b->title);
        author = new QTableWidgetItem(b->author);
        ISBN = new QTableWidgetItem(b->ISBN);
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
    RecieptViewer *reservedDisplay = new RecieptViewer(0, LibraryDB::instance()->GetAllReservations(), true);

    reservedDisplay->setWindowTitle("Reserved Books");

    reservedDisplay->exec();
}

void UserOptions::on_checkedOutListButton_clicked()
{
    RecieptViewer *checkedoutDisplay = new RecieptViewer(0, LibraryDB::instance()->GetAllCheckedOutBooks(), false);

    checkedoutDisplay->setWindowTitle("Checked out Books");

    checkedoutDisplay->exec();
}

void UserOptions::on_editUserButton_clicked()
{
    if(eu != NULL)
    {
        if(eu->isVisible())
        {
            eu->close();
        }

        delete eu;
    }

    UserBase *ref = LibraryDB::instance()->GetUser(ui->userInfoTable->item(ui->userInfoTable->currentRow(), 0)->text().toInt());
    eu = new editUser(0, ref->GetName(), ref->GetUsername(), LibraryDB::instance()->GetPass(ref->GetUsername()), ref->GetCardNumber(), ref->GetAddress(), ref->GetPhoneNumber(), false);
    eu->exec();

    ui->userInfoTable->clearContents();
    if(activeUserLevel == 2)
    {
        int userRow = 0;
        QStringList uheader = {"ID", "Name", "Access Level" };
        ui->userInfoTable->setColumnCount(3);
        ui->userInfoTable->setRowCount(LibraryDB::instance()->GetNumberOfUsers());
        ui->userInfoTable->setHorizontalHeaderLabels(uheader);

        foreach(UserBase* ub, LibraryDB::instance()->GetAllUsers())
        {
            userID = new QTableWidgetItem(QString::number(ub->GetCardNumber()));
            userName = new QTableWidgetItem(ub->GetName());
            userAccess = new QTableWidgetItem(QString::number(LibraryDB::instance()->Authenticate(ub)));

            ui->userInfoTable->setItem(userRow, 0, userID);
            ui->userInfoTable->setItem(userRow, 1, userName);
            ui->userInfoTable->setItem(userRow, 2, userAccess);

            userRow++;
        }

        ui->editUserButton->setEnabled(false);
        ui->removeUserButton->setEnabled(false);
    }
}

void UserOptions::on_userInfoTable_itemActivated(QTableWidgetItem *item)
{
    ui->editUserButton->setEnabled(true);
}

void UserOptions::on_borrowBookButton_clicked()
{
    LibraryDB::instance()->CheckOutBook(LibraryDB::instance()->GetUser(ui->userIdLineEdit->text().toInt()),
                                        LibraryDB::instance()->GetBook(ui->isbnLineEdit->text()),
                                        false,false);
}

void UserOptions::on_returnBookButton_clicked()
{
    LibraryDB::instance()->ReturnBook(ui->isbnLineEdit->text());
}

void UserOptions::on_reserveBookButton_clicked()
{
    LibraryDB::instance()->CheckOutBook(LibraryDB::instance()->GetUser(LibraryDB::instance()->GetActiveUser()),
                                        LibraryDB::instance()->GetBook(ui->tableWidget->item(ui->tableWidget->currentRow(), 2)->text()),
                                        false,true);
}

void UserOptions::on_userInfoTable_cellPressed(int row, int column)
{
    ui->editUserButton->setEnabled(true);
    ui->removeUserButton->setEnabled(true);
}

void UserOptions::on_addUserButton_clicked()
{
    if(eu != NULL)
    {
        if(eu->isVisible())
        {
            eu->close();
        }

        delete eu;
    }

    eu = new editUser(0, " ", " ", " ", 0, " ", " ", true);
    eu->exec();

    ui->userInfoTable->clearContents();
    if(activeUserLevel == 2)
    {
        int userRow = 0;
        QStringList uheader = {"ID", "Name", "Access Level" };
        ui->userInfoTable->setColumnCount(3);
        ui->userInfoTable->setRowCount(LibraryDB::instance()->GetNumberOfUsers());
        ui->userInfoTable->setHorizontalHeaderLabels(uheader);

        foreach(UserBase* ub, LibraryDB::instance()->GetAllUsers())
        {

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
}

void UserOptions::on_removeUserButton_clicked()
{
    QMessageBox *mbox = new QMessageBox();
    mbox->setWindowTitle("Removing User");
    mbox->setText("Are You sure?");
    mbox->addButton("Ok", QMessageBox::AcceptRole);
    mbox->addButton("Cancel", QMessageBox::RejectRole);
    connect(mbox, SIGNAL(accepted()), this, SLOT(RemoveUser()));
    connect(mbox, SIGNAL(rejected()), mbox, SLOT(close()));
    mbox->exec();
    disconnect(mbox, SIGNAL(accepted()), this, SLOT(RemoveUser()));

    ui->userInfoTable->clearContents();
    if(activeUserLevel == 2)
    {
        int userRow = 0;
        QStringList uheader = {"ID", "Name", "Access Level" };
        ui->userInfoTable->setColumnCount(3);
        ui->userInfoTable->setRowCount(LibraryDB::instance()->GetNumberOfUsers());
        ui->userInfoTable->setHorizontalHeaderLabels(uheader);

        foreach(UserBase* ub, LibraryDB::instance()->GetAllUsers())
        {
            userID = new QTableWidgetItem(QString::number(ub->GetCardNumber()));
            userName = new QTableWidgetItem(ub->GetName());
            userAccess = new QTableWidgetItem(QString::number(LibraryDB::instance()->Authenticate(ub)));

            ui->userInfoTable->setItem(userRow, 0, userID);
            ui->userInfoTable->setItem(userRow, 1, userName);
            ui->userInfoTable->setItem(userRow, 2, userAccess);

            userRow++;
        }

        ui->editUserButton->setEnabled(false);
        ui->removeUserButton->setEnabled(false);
    }
}

void UserOptions::on_addBookButton_clicked()
{
    if(eb != NULL)
    {
        if(eb->isVisible())
        {
            eb->close();
        }

        delete eb;
    }

    eb = new editBook();
    eb->exec();

    ui->tableWidget->clearContents();
    int i, row = 0;
    foreach(Book* b, LibraryDB::instance()->GetAllBooks())
    {
        if(i == 0) { i++ ; continue; }
        else if(i == 5662) { break; }
        else if(b->ISBN.toLongLong() == 0) { continue; }
        else { i++; }

        title = new QTableWidgetItem(b->title);
        author = new QTableWidgetItem(b->author);
        ISBN = new QTableWidgetItem(b->ISBN);
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

void UserOptions::on_editBookButton_clicked()
{
    if(eb != NULL)
    {
        if(eb->isVisible())
        {
            eb->close();
        }

        delete eb;
    }

    Book *ref = LibraryDB::instance()->GetBook(ui->tableWidget->itemAt(2, ui->tableWidget->currentRow())->text());
    eb = new editBook(0, ref->title, ref->author, ref->ISBN, ref->copiesAvailable.size(), ref->publisher, ref->publishYear, false);
    eb->exec();

    ui->tableWidget->clearContents();
    int i, row = 0;
    foreach(Book* b, LibraryDB::instance()->GetAllBooks())
    {
        if(i == 0) { i++ ; continue; }
        else if(i == 5662) { break; }
        else if(b->ISBN.toLongLong() == 0) { continue; }
        else { i++; }

        title = new QTableWidgetItem(b->title);
        author = new QTableWidgetItem(b->author);
        ISBN = new QTableWidgetItem(b->ISBN);
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

void UserOptions::on_removeBookButton_clicked()
{
    QMessageBox *mbox = new QMessageBox();
    mbox->setWindowTitle("Removing Book");
    mbox->setText("Are You sure?");
    mbox->addButton("Ok", QMessageBox::AcceptRole);
    mbox->addButton("Cancel", QMessageBox::RejectRole);
    connect(mbox, SIGNAL(accepted()), this, SLOT(RemoveBook()));
    connect(mbox, SIGNAL(rejected()), mbox, SLOT(close()));
    mbox->exec();
    disconnect(mbox, SIGNAL(accepted()), this, SLOT(RemoveBook()));

    ui->tableWidget->clearContents();
    int i, row = 0;
    foreach(Book* b, LibraryDB::instance()->GetAllBooks())
    {
        if(i == 0) { i++ ; continue; }
        else if(i == 5662) { break; }
        else if(b->ISBN.toLongLong() == 0) { continue; }
        else { i++; }

        title = new QTableWidgetItem(b->title);
        author = new QTableWidgetItem(b->author);
        ISBN = new QTableWidgetItem(b->ISBN);
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

void UserOptions::RemoveUser()
{
    LibraryDB::instance()->RemoveUser(ui->userInfoTable->itemAt(ui->userInfoTable->currentRow(), 0)->text().toInt());
}

void UserOptions::RemoveBook()
{
    LibraryDB::instance()->RemoveBook(ui->tableWidget->itemAt(ui->tableWidget->currentRow(), 2)->text());
}

void UserOptions::on_tableWidget_cellClicked(int row, int column)
{
    ui->removeBookButton->setEnabled(true);
    ui->reserveBookButton->setEnabled(true);

    if(row < ui->tableWidget->rowCount())
        ui->isbnLineEdit->setText(ui->tableWidget->item(row, 2)->text());
    else
        ui->isbnLineEdit->clear();
}

void UserOptions::on_oldPB_clicked()
{
    RecieptViewer *oldBookDisplay = new RecieptViewer(0, {}, false, LibraryDB::instance()->GetAllOldBooks(), true);
    oldBookDisplay->setWindowTitle("Retired Books");
    oldBookDisplay->exec();

    ui->tableWidget->clearContents();
    int i =0, row = 0;
    foreach(Book* b, LibraryDB::instance()->GetAllBooks())
    {
        if(i == 0) { i++ ; continue; }
        else if(i == 5662) { break; }
        else if(b->ISBN.toLongLong() == 0) { continue; }
        else { i++; }

        title = new QTableWidgetItem(b->title);
        author = new QTableWidgetItem(b->author);
        ISBN = new QTableWidgetItem(b->ISBN);
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
