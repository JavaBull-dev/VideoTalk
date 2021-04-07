#include "serversetdialog.h"
#include "ui_serversetdialog.h"

ServerSetDialog::ServerSetDialog(QString ip, int ctrlPort, int dataPort, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerSetDialog)
{
    ui->setupUi(this);
    ui->lineEdit_ip->setText(ip);
    ui->lineEdit_ctrlPort->setText(QString::number(ctrlPort));
    ui->lineEdit_dataPort->setText(QString::number(dataPort));
}

ServerSetDialog::~ServerSetDialog()
{
    delete ui;
}

QString ServerSetDialog::getIp()
{
    return ui->lineEdit_ip->text();
}

QString ServerSetDialog::getCtrlPort()
{
    return ui->lineEdit_ctrlPort->text();
}

QString ServerSetDialog::getDataPort()
{
    return ui->lineEdit_dataPort->text();
}
