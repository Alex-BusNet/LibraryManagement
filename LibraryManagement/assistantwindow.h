#ifndef ASSISTANTWINDOW_H
#define ASSISTANTWINDOW_H

#include <QDialog>

namespace Ui {
class assistantWindow;
}

class assistantWindow : public QDialog
{
    Q_OBJECT

public:
    explicit assistantWindow(QWidget *parent = 0);
    ~assistantWindow();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::assistantWindow *ui;
};

#endif // ASSISTANTWINDOW_H
