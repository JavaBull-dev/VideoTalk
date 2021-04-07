#ifndef CLOSEWAITDIALOG_H
#define CLOSEWAITDIALOG_H

#include <QDialog>

namespace Ui {
class CloseWaitDialog;
}

class CloseWaitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CloseWaitDialog(QWidget *parent = nullptr);
    ~CloseWaitDialog();

private:
    Ui::CloseWaitDialog *ui;
};

#endif // CLOSEWAITDIALOG_H
