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
    explicit editBook(QWidget *parent = 0);
    ~editBook();

private:
    Ui::editBook *ui;
};

#endif // EDITBOOK_H
