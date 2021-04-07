/********************************************************************************
** Form generated from reading UI file 'closewaitdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOSEWAITDIALOG_H
#define UI_CLOSEWAITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CloseWaitDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QDialog *CloseWaitDialog)
    {
        if (CloseWaitDialog->objectName().isEmpty())
            CloseWaitDialog->setObjectName(QString::fromUtf8("CloseWaitDialog"));
        CloseWaitDialog->resize(350, 65);
        verticalLayout = new QVBoxLayout(CloseWaitDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(CloseWaitDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        progressBar = new QProgressBar(CloseWaitDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setCursor(QCursor(Qt::BusyCursor));
        progressBar->setValue(24);
        progressBar->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setInvertedAppearance(false);

        verticalLayout->addWidget(progressBar);


        retranslateUi(CloseWaitDialog);

        QMetaObject::connectSlotsByName(CloseWaitDialog);
    } // setupUi

    void retranslateUi(QDialog *CloseWaitDialog)
    {
        CloseWaitDialog->setWindowTitle(QApplication::translate("CloseWaitDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("CloseWaitDialog", "\347\255\211\345\276\205\347\250\213\345\272\217\345\205\263\351\227\255", nullptr));
        progressBar->setFormat(QString());
    } // retranslateUi

};

namespace Ui {
    class CloseWaitDialog: public Ui_CloseWaitDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOSEWAITDIALOG_H
