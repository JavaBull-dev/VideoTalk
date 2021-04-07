/********************************************************************************
** Form generated from reading UI file 'logdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGDIALOG_H
#define UI_LOGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LogDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextEdit *textEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LogDialog)
    {
        if (LogDialog->objectName().isEmpty())
            LogDialog->setObjectName(QString::fromUtf8("LogDialog"));
        LogDialog->resize(578, 486);
        verticalLayout = new QVBoxLayout(LogDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(LogDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        textEdit = new QTextEdit(LogDialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);

        buttonBox = new QDialogButtonBox(LogDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(LogDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), LogDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), LogDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(LogDialog);
    } // setupUi

    void retranslateUi(QDialog *LogDialog)
    {
        LogDialog->setWindowTitle(QApplication::translate("LogDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("LogDialog", "\347\250\213\345\272\217\350\277\220\350\241\214\346\227\245\345\277\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogDialog: public Ui_LogDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGDIALOG_H
