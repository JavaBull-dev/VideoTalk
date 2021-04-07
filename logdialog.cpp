#include "logdialog.h"
#include "ui_logdialog.h"

LogDialog::LogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogDialog)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    setWindowTitle(tr("日志信息"));
}

LogDialog::~LogDialog()
{
    delete ui;
}

void LogDialog::setLog(QString msg)
{
    ui->textEdit->setText(msg);
}
