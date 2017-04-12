#ifndef USEROPTIONS_H
#define USEROPTIONS_H

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

    void on_pushButton_clicked();

private:
    Ui::UserOptions *ui;
    int activeUserLevel;


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
