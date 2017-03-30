#ifndef USEROPTIONS_H
#define USEROPTIONS_H

#include <QMainWindow>

namespace Ui {
class UserOptions;
}

class UserOptions : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserOptions(QWidget *parent = 0);
    ~UserOptions();

private slots:
    void on_save_quit_button_clicked();

    void on_save_button_clicked();

    void on_book_table_doubleClicked(const QModelIndex &index);
    
private:
    Ui::UserOptions *ui;
};

#endif // USEROPTIONS_H
