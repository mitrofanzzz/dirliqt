#ifndef DIALOG_SETDIR_H
#define DIALOG_SETDIR_H

#include <QDialog>

namespace Ui {
class Dialog_setdir;
}

class Dialog_setdir : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_setdir(QWidget *parent = 0);
    ~Dialog_setdir();

private:
    Ui::Dialog_setdir *ui;
};

#endif // DIALOG_SETDIR_H
