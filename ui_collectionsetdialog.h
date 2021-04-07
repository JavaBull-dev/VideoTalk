/********************************************************************************
** Form generated from reading UI file 'collectionsetdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLLECTIONSETDIALOG_H
#define UI_COLLECTIONSETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CollectionSetDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_audioInput;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBox_camera;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CollectionSetDialog)
    {
        if (CollectionSetDialog->objectName().isEmpty())
            CollectionSetDialog->setObjectName(QString::fromUtf8("CollectionSetDialog"));
        CollectionSetDialog->resize(564, 204);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CollectionSetDialog->sizePolicy().hasHeightForWidth());
        CollectionSetDialog->setSizePolicy(sizePolicy);
        CollectionSetDialog->setMinimumSize(QSize(363, 204));
        CollectionSetDialog->setMaximumSize(QSize(6666666, 204));
        verticalLayout = new QVBoxLayout(CollectionSetDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CollectionSetDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        comboBox_audioInput = new QComboBox(CollectionSetDialog);
        comboBox_audioInput->setObjectName(QString::fromUtf8("comboBox_audioInput"));

        horizontalLayout->addWidget(comboBox_audioInput);

        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(CollectionSetDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_2);

        comboBox_camera = new QComboBox(CollectionSetDialog);
        comboBox_camera->setObjectName(QString::fromUtf8("comboBox_camera"));

        horizontalLayout_2->addWidget(comboBox_camera);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        buttonBox = new QDialogButtonBox(CollectionSetDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(CollectionSetDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CollectionSetDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CollectionSetDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CollectionSetDialog);
    } // setupUi

    void retranslateUi(QDialog *CollectionSetDialog)
    {
        CollectionSetDialog->setWindowTitle(QApplication::translate("CollectionSetDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("CollectionSetDialog", "\351\237\263\351\242\221\350\256\276\345\244\207", nullptr));
        label_2->setText(QApplication::translate("CollectionSetDialog", "\350\247\206\351\242\221\350\256\276\345\244\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CollectionSetDialog: public Ui_CollectionSetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLLECTIONSETDIALOG_H
