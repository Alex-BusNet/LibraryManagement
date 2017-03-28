#include "useroptions.h"
#include "ui_useroptions.h"

userOptions::userOptions(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userOptions)
{
    ui->setupUi(this);
}

userOptions::~userOptions()
{
    delete ui;
}
