#ifndef EDITBOOK_H
#define EDITBOOK_H

#include <QDialog>

namespace Ui {
class editBook;
}

class editBook : public QDialog
{
    Q_OBJECT

public:
    explicit editBook(QWidget *parent = 0, QString title = " ", QString author = " " , QString ISBN = " ", int copies = 3, QString publisher = " ", int publishYear = 1988, bool newBook = true);
    ~editBook();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::editBook *ui;
    bool newBook;
};

#endif // EDITBOOK_H
