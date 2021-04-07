#ifndef SERVERSETDIALOG_H
#define SERVERSETDIALOG_H

#include <QDialog>

namespace Ui {
class ServerSetDialog;
}

class ServerSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerSetDialog(QString ip, int ctrlPort, int dataPort, QWidget *parent = nullptr);
    ~ServerSetDialog();
    QString getIp();
    QString getCtrlPort();
    QString getDataPort();
private:
    Ui::ServerSetDialog *ui;
};

#endif // SERVERSETDIALOG_H
