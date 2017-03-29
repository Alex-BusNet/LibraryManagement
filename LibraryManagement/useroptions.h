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

private:
    Ui::UserOptions *ui;
};

#endif // USEROPTIONS_H
