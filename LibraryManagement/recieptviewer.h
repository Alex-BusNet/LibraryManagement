#ifndef RECIEPTVIEWER_H
#define RECIEPTVIEWER_H

#include <QDialog>
#include <QTableWidget>
#include "librarydb.h"

namespace Ui {
class RecieptViewer;
}

class RecieptViewer : public QDialog
{
    Q_OBJECT

public:
    explicit RecieptViewer(QWidget *parent = 0, QVector<BookReciept *> recieptVector = {}, bool reservationList = false, QVector<Book*> oldVector = {}, bool oldList = false);
    ~RecieptViewer();

    void paintEvent(QPaintEvent *event);

private:
    Ui::RecieptViewer *ui;
    bool resList, obList;

private slots:
    void on_bookActionPB_clicked();
    void on_tw_itemActivated(QTableWidgetItem *item);
    void on_closePB_clicked();
    void on_tw_itemClicked(QTableWidgetItem *item);
};

#endif // RECIEPTVIEWER_H
