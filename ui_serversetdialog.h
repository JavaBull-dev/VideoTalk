/********************************************************************************
** Form generated from reading UI file 'serversetdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERSETDIALOG_H
#define UI_SERVERSETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ServerSetDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_ip;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_dataPort;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_ctrlPort;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ServerSetDialog)
    {
        if (ServerSetDialog->objectName().isEmpty())
            ServerSetDialog->setObjectName(QString::fromUtf8("ServerSetDialog"));
        ServerSetDialog->resize(263, 203);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ServerSetDialog->sizePolicy().hasHeightForWidth());
        ServerSetDialog->setSizePolicy(sizePolicy);
        ServerSetDialog->setMaximumSize(QSize(263, 203));
        verticalLayout = new QVBoxLayout(ServerSetDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(ServerSetDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit_ip = new QLineEdit(ServerSetDialog);
        lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));

        horizontalLayout->addWidget(lineEdit_ip);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(ServerSetDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_dataPort = new QLineEdit(ServerSetDialog);
        lineEdit_dataPort->setObjectName(QString::fromUtf8("lineEdit_dataPort"));

        horizontalLayout_2->addWidget(lineEdit_dataPort);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(ServerSetDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_ctrlPort = new QLineEdit(ServerSetDialog);
        lineEdit_ctrlPort->setObjectName(QString::fromUtf8("lineEdit_ctrlPort"));

        horizontalLayout_3->addWidget(lineEdit_ctrlPort);


        verticalLayout->addLayout(horizontalLayout_3);

        buttonBox = new QDialogButtonBox(ServerSetDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ServerSetDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ServerSetDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ServerSetDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ServerSetDialog);
    } // setupUi

    void retranslateUi(QDialog *ServerSetDialog)
    {
        ServerSetDialog->setWindowTitle(QApplication::translate("ServerSetDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("ServerSetDialog", "\346\234\215\345\212\241\345\231\250ip", nullptr));
        label_2->setText(QApplication::translate("ServerSetDialog", "\346\225\260\346\215\256\347\253\257\345\217\243", nullptr));
        label_3->setText(QApplication::translate("ServerSetDialog", "\346\216\247\345\210\266\347\253\257\345\217\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerSetDialog: public Ui_ServerSetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERSETDIALOG_H
