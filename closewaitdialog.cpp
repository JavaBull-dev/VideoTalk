#include "closewaitdialog.h"
#include "ui_closewaitdialog.h"

CloseWaitDialog::CloseWaitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CloseWaitDialog)
{
    ui->setupUi(this);
    //忙等待
    ui->progressBar->setMaximum(0);
    ui->progressBar->setMinimum(0);

    setWindowTitle(tr("正在关闭"));
}

CloseWaitDialog::~CloseWaitDialog()
{
    delete ui;
}
