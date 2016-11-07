#include "dialog_setdir.h"
#include "ui_dialog_setdir.h"

Dialog_setdir::Dialog_setdir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_setdir)
{
    ui->setupUi(this);
}

Dialog_setdir::~Dialog_setdir()
{
    delete ui;
}
