#ifndef USEROPTIONS_H
#define USEROPTIONS_H

#include "editbook.h"
#include "edituser.h"

#include <QWidget>
#include <ui_useroptions.h>

namespace Ui {
class UserOptions;
}

class UserOptions : public QWidget
{
    Q_OBJECT

public:
    explicit UserOptions(QWidget *parent = 0, int userLevel = 0);
    void paintEvent(QPaintEvent *e);
    ~UserOptions();

private slots:
    void on_save_quit_button_clicked();

    void on_save_button_clicked();
    
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_searchButton_clicked();

    void on_reservedListButton_clicked();

    void on_checkedOutListButton_clicked();

    void on_editUserButton_clicked();

    void on_userInfoTable_itemActivated(QTableWidgetItem *item);

    void on_borrowBookButton_clicked();

    void on_returnBookButton_clicked();

    void on_reserveBookButton_clicked();

    void on_userInfoTable_cellPressed(int row, int column);

    void on_addUserButton_clicked();

    void on_removeUserButton_clicked();

    void on_addBookButton_clicked();

    void on_editBookButton_clicked();

    void on_removeBookButton_clicked();

    void RemoveUser();

    void RemoveBook();

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::UserOptions *ui;
    int activeUserLevel;

    editUser* eu;
    editBook* eb;

    QTableWidgetItem *title;
    QTableWidgetItem *author;
    QTableWidgetItem *ISBN;
    QTableWidgetItem *copies;
    QTableWidgetItem *longTerm;
    QTableWidgetItem *publisher;
    QTableWidgetItem *publishYear;
    QTableWidgetItem *userID;
    QTableWidgetItem *userName;
    QTableWidgetItem *userAccess;

};

#endif // USEROPTIONS_H
