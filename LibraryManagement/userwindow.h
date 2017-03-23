#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QDialog>

namespace Ui {
class userWindow;
}

class userWindow : public QDialog
{
    Q_OBJECT

public:
    explicit userWindow(QWidget *parent = 0);
    ~userWindow();

private slots:
    void on_tableWidget_2_itemClicked(QTableWidgetItem *item);

private:
    Ui::userWindow *ui;
};

#endif // USERWINDOW_H
