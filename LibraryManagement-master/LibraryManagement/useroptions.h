#ifndef USEROPTIONS_H
#define USEROPTIONS_H

#include <QMainWindow>

namespace Ui {
class userOptions;
}

class userOptions : public QMainWindow
{
    Q_OBJECT

public:
    explicit userOptions(QWidget *parent = 0);
    ~userOptions();

private:
    Ui::userOptions *ui;
};

#endif // USEROPTIONS_H
