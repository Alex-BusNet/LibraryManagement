#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "useroptions.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_login_clicked();

private:
    Ui::MainWindow *ui;
    UserOptions *uo;
};

#endif // MAINWINDOW_H
