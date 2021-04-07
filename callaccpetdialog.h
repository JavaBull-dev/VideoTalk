#ifndef CALLACCPETDIALOG_H
#define CALLACCPETDIALOG_H

#include <QDialog>

namespace Ui {
class CallAccpetDialog;
}

class CallAccpetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CallAccpetDialog(QWidget *parent = nullptr);
    ~CallAccpetDialog();

private:
    Ui::CallAccpetDialog *ui;
};

#endif // CALLACCPETDIALOG_H
