#include "datatypes.h"
#include "recieptviewer.h"
#include "ui_recieptviewer.h"

RecieptViewer::RecieptViewer(QWidget *parent, QVector<BookReciept*> recieptVector, bool reservationList, QVector<Book*> oldVector, bool oldList) :
    QDialog(parent),
    ui(new Ui::RecieptViewer)
{
    ui->setupUi(this);

    ui->bookActionPB->setEnabled(false);
    ui->tw->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setLayout(ui->verticalLayout);

    if(reservationList)
    {
        ui->bookActionPB->setText("Fulfill Reservation");
    }
    else if(oldList)
    {
        ui->bookActionPB->setText("Restore Book");
    }
    else
    {
        ui->bookActionPB->setText("Return Book");
    }

    if(!oldList)
    {
        this->setFixedWidth(450);
        ui->tw->setColumnCount(4);
        QStringList twheader = {"User Number", "ISBN", "Pickup Date" , "Needs Reminder"};
        ui->tw->setHorizontalHeaderLabels(twheader);
        ui->tw->setSortingEnabled(true);
        ui->tw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        int row = 0;
        QTableWidgetItem* userNo;
        QTableWidgetItem* isbn;
        QTableWidgetItem* duedate;
        QTableWidgetItem* needsreminder;

        ui->tw->setRowCount(recieptVector.size());

        foreach(BookReciept *br, recieptVector)
        {
            userNo = new QTableWidgetItem(QString::number(br->userNo));
            isbn = new QTableWidgetItem(br->ISBN);
            duedate = new QTableWidgetItem(br->dateDue.toString());
            needsreminder = new QTableWidgetItem((br->needsReminder ? "True" : "False"));

            ui->tw->setItem(row, 0, userNo);
            ui->tw->setItem(row, 1, isbn);
            ui->tw->setItem(row, 2, duedate);
            ui->tw->setItem(row, 3, needsreminder);

            row++;
        }
    }
    else
    {
        this->setFixedWidth(900);
        ui->tw->setColumnCount(7);

        QStringList twheader = {"Title", "Author", "ISBN", "Copies Available", "Check-out period", "Publisher" , "Year Published"};
        ui->tw->setHorizontalHeaderLabels(twheader);
        ui->tw->setSortingEnabled(true);
        ui->tw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        int i = 0, row = 0;
        QTableWidgetItem *title;
        QTableWidgetItem *author;
        QTableWidgetItem *ISBN;
        QTableWidgetItem *copies;
        QTableWidgetItem *longTerm;
        QTableWidgetItem *publisher;
        QTableWidgetItem *publishYear;

        foreach(Book* b, oldVector)
        {
            if(b->ISBN.toLongLong() == 0) { continue; }
            else { i++; }

            title = new QTableWidgetItem(b->title);
            author = new QTableWidgetItem(b->author);
            ISBN = new QTableWidgetItem(b->ISBN);
            copies = new QTableWidgetItem(QString::number(LibraryDB::instance()->GetCopiesOfBook(b->ISBN)));
            longTerm = new QTableWidgetItem((b->longTerm) ? "4 Weeks" : "1 Week");
            publisher = new QTableWidgetItem(b->publisher);
            publishYear = new QTableWidgetItem(QString::number(b->publishYear));

            ui->tw->setItem(row, 0, title);
            ui->tw->setItem(row, 1, author);
            ui->tw->setItem(row, 2, ISBN);
            ui->tw->setItem(row, 3, copies);
            ui->tw->setItem(row, 4, longTerm);
            ui->tw->setItem(row, 5, publisher);
            ui->tw->setItem(row, 6, publishYear);

            row++;
        }
    }
    resList = reservationList;
    obList = oldList;
}

RecieptViewer::~RecieptViewer()
{
    delete ui;
}

void RecieptViewer::paintEvent(QPaintEvent *event)
{
    if(ui->tw->selectedItems().isEmpty())
    {
        ui->bookActionPB->clearFocus();
        ui->bookActionPB->setEnabled(false);
    }
}

void RecieptViewer::on_bookActionPB_clicked()
{
    Book *b;
    BookReciept *br;
    if(!obList)
    {
        br  = new BookReciept{ui->tw->item(ui->tw->currentRow(), 0)->text().toInt(),
                                            ui->tw->item(ui->tw->currentRow(), 1)->text(),
                                            QDate().fromString(ui->tw->item(ui->tw->currentRow(), 2)->text()),
                                            (ui->tw->item(ui->tw->currentRow(), 3)->text() == "false" ? false : true)
                                            };
    }
    else
    {
        b = new Book{ui->tw->item(ui->tw->currentRow(), 0)->text(),
                            ui->tw->item(ui->tw->currentRow(), 1)->text(),
                            ui->tw->item(ui->tw->currentRow(), 2)->text(),
                            QVector<int>{-1, -1, -1},
                            (ui->tw->item(ui->tw->currentRow(), 4)->text() == "False" ? false : true),
                            ui->tw->item(ui->tw->currentRow(), 5)->text(),
                            ui->tw->item(ui->tw->currentRow(), 6)->text().toInt()
                            };

    }

    if(resList)
    {
        LibraryDB::instance()->FulfillReservation(br);
        ui->tw->clearContents();

        int row = 0;
        QTableWidgetItem* userNo;
        QTableWidgetItem* isbn;
        QTableWidgetItem* duedate;
        QTableWidgetItem* needsreminder;

        ui->tw->setRowCount(LibraryDB::instance()->GetAllReservations().size());

        foreach(BookReciept *br, LibraryDB::instance()->GetAllReservations())
        {
            userNo = new QTableWidgetItem(QString::number(br->userNo));
            isbn = new QTableWidgetItem(br->ISBN);
            duedate = new QTableWidgetItem(br->dateDue.toString());
            needsreminder = new QTableWidgetItem((br->needsReminder ? "True" : "False"));

            ui->tw->setItem(row, 0, userNo);
            ui->tw->setItem(row, 1, isbn);
            ui->tw->setItem(row, 2, duedate);
            ui->tw->setItem(row, 3, needsreminder);

            row++;
        }
    }
    else if(obList)
    {
        LibraryDB::instance()->AddBook(b);
        int i = 0, row = 0;
        QTableWidgetItem *title;
        QTableWidgetItem *author;
        QTableWidgetItem *ISBN;
        QTableWidgetItem *copies;
        QTableWidgetItem *longTerm;
        QTableWidgetItem *publisher;
        QTableWidgetItem *publishYear;

        foreach(Book* b, LibraryDB::instance()->GetAllOldBooks())
        {
            if(b->ISBN.toLongLong() == 0) { continue; }
            else { i++; }

            title = new QTableWidgetItem(b->title);
            author = new QTableWidgetItem(b->author);
            ISBN = new QTableWidgetItem(b->ISBN);
            copies = new QTableWidgetItem(QString::number(LibraryDB::instance()->GetCopiesOfBook(b->ISBN)));
            longTerm = new QTableWidgetItem((b->longTerm) ? "4 Weeks" : "1 Week");
            publisher = new QTableWidgetItem(b->publisher);
            publishYear = new QTableWidgetItem(QString::number(b->publishYear));

            ui->tw->setItem(row, 0, title);
            ui->tw->setItem(row, 1, author);
            ui->tw->setItem(row, 2, ISBN);
            ui->tw->setItem(row, 3, copies);
            ui->tw->setItem(row, 4, longTerm);
            ui->tw->setItem(row, 5, publisher);
            ui->tw->setItem(row, 6, publishYear);

            row++;
        }
    }
    else
    {
        LibraryDB::instance()->ReturnBook(br->ISBN);
        ui->tw->clearContents();

        int row = 0;
        QTableWidgetItem* userNo;
        QTableWidgetItem* isbn;
        QTableWidgetItem* duedate;
        QTableWidgetItem* needsreminder;

        ui->tw->setRowCount(LibraryDB::instance()->GetAllCheckedOutBooks().size());

        foreach(BookReciept *br, LibraryDB::instance()->GetAllCheckedOutBooks())
        {
            userNo = new QTableWidgetItem(QString::number(br->userNo));
            isbn = new QTableWidgetItem(br->ISBN);
            duedate = new QTableWidgetItem(br->dateDue.toString());
            needsreminder = new QTableWidgetItem((br->needsReminder ? "True" : "False"));

            ui->tw->setItem(row, 0, userNo);
            ui->tw->setItem(row, 1, isbn);
            ui->tw->setItem(row, 2, duedate);
            ui->tw->setItem(row, 3, needsreminder);

            row++;
        }
    }

    ui->bookActionPB->clearFocus();
    ui->bookActionPB->setEnabled(false);
}

void RecieptViewer::on_tw_itemActivated(QTableWidgetItem *item)
{
    ui->bookActionPB->setEnabled(true);
}


void RecieptViewer::on_closePB_clicked()
{
    this->close();
}

void RecieptViewer::on_tw_itemClicked(QTableWidgetItem *item)
{
    ui->bookActionPB->setEnabled(true);
}
