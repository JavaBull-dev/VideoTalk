#include "callaccpetdialog.h"
#include "ui_callaccpetdialog.h"

CallAccpetDialog::CallAccpetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CallAccpetDialog)
{
    ui->setupUi(this);
    ui->progressBar->setMaximum(0);
    ui->progressBar->setMinimum(0);
    setWindowTitle(tr("通话请求"));
}

CallAccpetDialog::~CallAccpetDialog()
{
    delete ui;
}
