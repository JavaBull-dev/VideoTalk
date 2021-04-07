#include "mainwindow.h"
#include <QApplication>
//#include <QTextkCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForLocale(codec);
    MainWindow w;
    w.setWindowTitle(QString::fromUtf8("VideoTalk"));
    //禁用最大化按钮
    w.setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    w.show();
//    qDebug("%d", sizeof(QCamera));
    return a.exec();
}
