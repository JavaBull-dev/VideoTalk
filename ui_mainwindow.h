/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "openglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_exit;
    QAction *action_serverSet;
    QAction *action_font;
    QAction *action_userInfoSet;
    QAction *action_help;
    QAction *action_about;
    QAction *action_collectionSet;
    QAction *action_log;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_username;
    QLabel *label_2;
    QLineEdit *lineEdit_peername;
    QPushButton *pushButton_call;
    QSpacerItem *horizontalSpacer;
    OpenGLWidget *openGLWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(786, 761);
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QString::fromUtf8("action_exit"));
        action_serverSet = new QAction(MainWindow);
        action_serverSet->setObjectName(QString::fromUtf8("action_serverSet"));
        action_font = new QAction(MainWindow);
        action_font->setObjectName(QString::fromUtf8("action_font"));
        action_userInfoSet = new QAction(MainWindow);
        action_userInfoSet->setObjectName(QString::fromUtf8("action_userInfoSet"));
        action_help = new QAction(MainWindow);
        action_help->setObjectName(QString::fromUtf8("action_help"));
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QString::fromUtf8("action_about"));
        action_collectionSet = new QAction(MainWindow);
        action_collectionSet->setObjectName(QString::fromUtf8("action_collectionSet"));
        action_log = new QAction(MainWindow);
        action_log->setObjectName(QString::fromUtf8("action_log"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit_username = new QLineEdit(centralWidget);
        lineEdit_username->setObjectName(QString::fromUtf8("lineEdit_username"));

        horizontalLayout->addWidget(lineEdit_username);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_peername = new QLineEdit(centralWidget);
        lineEdit_peername->setObjectName(QString::fromUtf8("lineEdit_peername"));

        horizontalLayout->addWidget(lineEdit_peername);

        pushButton_call = new QPushButton(centralWidget);
        pushButton_call->setObjectName(QString::fromUtf8("pushButton_call"));

        horizontalLayout->addWidget(pushButton_call);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        openGLWidget = new OpenGLWidget(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));

        verticalLayout->addWidget(openGLWidget);

        verticalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 786, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(action_exit);
        menu->addAction(action_log);
        menu_2->addAction(action_font);
        menu_3->addAction(action_help);
        menu_3->addAction(action_about);
        menu_3->addSeparator();
        menu_4->addAction(action_serverSet);
        menu_4->addSeparator();
        menu_4->addAction(action_userInfoSet);
        menu_4->addAction(action_collectionSet);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action_exit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        action_serverSet->setText(QApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\350\256\276\347\275\256", nullptr));
        action_font->setText(QApplication::translate("MainWindow", "\345\255\227\344\275\223\350\256\276\347\275\256", nullptr));
        action_userInfoSet->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\344\277\241\346\201\257\350\256\276\347\275\256", nullptr));
        action_help->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213\345\270\256\345\212\251", nullptr));
        action_about->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        action_collectionSet->setText(QApplication::translate("MainWindow", "\351\207\207\351\233\206\350\256\276\345\244\207\350\256\276\347\275\256", nullptr));
        action_log->setText(QApplication::translate("MainWindow", "\346\227\245\345\277\227", nullptr));
        label->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\346\230\265\347\247\260", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\345\217\267\347\240\201", nullptr));
        pushButton_call->setText(QApplication::translate("MainWindow", "\346\213\250\345\217\267", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QApplication::translate("MainWindow", "\346\240\274\345\274\217", nullptr));
        menu_3->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        menu_4->setTitle(QApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
