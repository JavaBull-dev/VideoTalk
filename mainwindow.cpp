#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serversetdialog.h"
#include "collectionsetdialog.h"
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QDebug>
#include <QMetaType>
#include <QtConcurrent>
#include "customeevent.h"
#include "logdialog.h"
#include <QTime>
#include "closewaitdialog.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_serverSet, SIGNAL(triggered()), this, SLOT(action_serverSet_slot()));

    connect(ui->action_exit, SIGNAL(triggered()), this, SLOT(action_exit_slot()));

    connect(ui->action_font, SIGNAL(triggered()), this, SLOT(action_font_slot()));

    connect(ui->pushButton_call, SIGNAL(clicked()), this, SLOT(pushButton_call_slot()));

    connect(ui->action_userInfoSet, SIGNAL(triggered()), this, SLOT(action_user_info_set_slot()));

    connect(ui->action_help, SIGNAL(triggered()), this, SLOT(action_help_slot()));

    connect(ui->action_about, SIGNAL(triggered()), this, SLOT(action_about_slot()));

    connect(ui->action_log, SIGNAL(triggered()), SLOT(action_log_slot()));

    serverSetting.ip = "127.0.0.1";//服务器的地址
    serverSetting.ctrlPort = 8888;//服务器的控制端口
    serverSetting.dataPort = 8889;//服务器的数据传输端口

    userSetting.nick = "小王";
    userSetting.number = "123456789";

    //设置默认值
    ui->lineEdit_username->setText(tr("小李"));
    ui->lineEdit_peername->setText(QString::fromUtf8("123456788"));

    ffmpeg = new IFFmpeg(this);
    ffmpegAudio = new IFFmpegAudio(ffmpeg, this);
    ffmpegVideo = new FFmpegVideo(ffmpeg, ffmpegAudio, this);

    connect(ffmpeg, SIGNAL(startProcessSignal()), ffmpegVideo, SLOT(startProcessSlot()));
    connect(ffmpeg, SIGNAL(startProcessSignal()), ffmpegAudio, SLOT(startProcessSlot()));

    connect(ffmpegVideo, SIGNAL(initParamSignal(IFFmpeg*, FFmpegVideo*)),
            ui->openGLWidget, SLOT(initParamSlot(IFFmpeg*, FFmpegVideo*)));

    connect(ffmpegVideo, SIGNAL(destoryParamSignal()),
            ui->openGLWidget, SLOT(destoryParamSlot()));

    //记录mainwindow的最大值和最小值
    winMaxSize = maximumSize().width();
    winMinSize = minimumSize().width();

    connect(ui->action_collectionSet, SIGNAL(triggered()), this, SLOT(action_collectionSet_slot()));

    info.audioDeviceName = "";
    info.videoDeviceName = "";

    //注册数据类型
//    qRegisterMetaType<AVStream>("AVStream");
//    qRegisterMetaType<AVPixelFormat>("AVPixelFormat");
//    qRegisterMetaType<AVFrame>("AVFrame");
//    qRegisterMetaType<int64_t>("int64_t");

    outputStream = new AVOutputStream(this);
    inputStream = new AVInputStream(outputStream, this);

//    connect(inputStream, SIGNAL(VideoCaptureCallback(AVStream*, enum AVPixelFormat, AVFrame*, int64_t)),
//            this, SLOT(VideoCaptureCallback(AVStream*, enum AVPixelFormat, AVFrame*, int64_t)));

//    connect(inputStream, SIGNAL(AudioCaptureCallback(AVStream*, AVFrame*, int64_t)),
//            this, SLOT(AudioCaptureCallback(AVStream*, AVFrame*, int64_t)));
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::closeEvent
 * @param event
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(event->type() == QEvent::Close)
    {
        QMessageBox box(this);
        box.setIcon(QMessageBox::Question);
        box.setText(tr("是否退出？"));
        box.setWindowTitle(tr("程序提示"));
        box.addButton(tr("确定"), QMessageBox::AcceptRole);
        box.addButton(tr("取消"), QMessageBox::RejectRole);
        int ret = box.exec();
        if(ret == QMessageBox::AcceptRole)
        {
            if(ffmpeg->isRunning())
            {
                ffmpeg->toStop();
                CloseWaitDialog d(this);
                QtConcurrent::run(MainWindow::closeApplication, this);
                d.exec();
            }
        }
        else
        {
            event->ignore();//忽略关闭事件
        }
    }
}

/**
 * @brief MainWindow::event
 * @param event
 * @return
 * 拦截自定义的事件来处理，执行对于的逻辑
 */
bool MainWindow::event(QEvent *event)
{
    if (event->type() == CustomeEvent::type) {
        CustomeEvent *myEvent = static_cast<CustomeEvent *>(event);
        switch (myEvent->getId()) {
        case CustomeEvent::ID::OPEN_ERROR:
            ui->pushButton_call->setText("拨号");
            ui->pushButton_call->setEnabled(true);
            break;
        case CustomeEvent::ID::CALL_SUCCESS:
            ui->pushButton_call->setText("挂断");
            ui->pushButton_call->setEnabled(true);
            break;
        case CustomeEvent::ID::STOP_SUCCESS:
            setMinimumSize(winMinSize, winMinSize);
            setMaximumSize(winMaxSize, winMaxSize);
            ui->pushButton_call->setEnabled(true);
            break;
        case CustomeEvent::ID::CLOSE_APP:
            ui->pushButton_call->setEnabled(true);
            exit(0);
        default:
            break;
        }
        return true;
    }

    return QMainWindow::event(event);
}

/**
 * @brief MainWindow::startCall
 * @param mainwindow
 * 拨号线程方法
 */
void MainWindow::startCall(MainWindow *m)
{
    /////////////////开始采集和传输视频/////////////////
    m->inputStream->setAudioCaptureDevice(m->info.audioDeviceName);
    m->inputStream->setVideoCaptureDevice(m->info.videoDeviceName);

    if(!m->inputStream->openInputStream())
    {
        QApplication::postEvent(m, new CustomeEvent(CustomeEvent::ID::OPEN_ERROR));
        m->log = m->log.append(addLogPrefix("open device failure"));
        qDebug("open device failure");
        return;
    }

    int cx, cy, fps;
    AVPixelFormat pixel_fmt;
    if(m->inputStream->getVideoInputInfo(cx, cy, fps, pixel_fmt)) //获取视频采集源的信息
    {
        m->outputStream->SetVideoCodecProp(AV_CODEC_ID_H264, fps, 500000, 100, cx, cy); //设置视频编码器属性
    }

    int sample_rate = 0, channels = 0;
    AVSampleFormat  sample_fmt;
    if(m->inputStream->getAudioInputInfo(sample_fmt, sample_rate, channels)) //获取音频采集源的信息
    {
        m->outputStream->SetAudioCodecProp(AV_CODEC_ID_AAC, sample_rate, channels, 32000); //设置音频编码器属性
    }

    if(!m->outputStream->OpenOutputStream("udp://127.0.0.1:12345"))
    {
        QApplication::postEvent(m, new CustomeEvent(CustomeEvent::ID::OPEN_ERROR));
        m->log = m->log.append(addLogPrefix("open output failure!"));
        qDebug("open output failure!");
        return;
    }

	QThread::msleep(10);
    if(!m->inputStream->startCapture())
    {
        QApplication::postEvent(m, new CustomeEvent(CustomeEvent::ID::OPEN_ERROR));
        m->log = m->log.append(addLogPrefix("start capture failure!"));
        qDebug("start capture failure!");
        return;
    }

//    QThread::msleep(500);
    ///////////////开始获取视频///////////////////
    if(!m->ffmpeg->isRunning())
    {
        QString url = "udp://127.0.0.1:12345";
        int ret = m->ffmpeg->openStream(url);
        if(ret>=0)
        {
            m->ffmpeg->start();
            m->log = m->log.append(addLogPrefix("启动ffmpeg成功"));
            qDebug("启动ffmpeg成功");
        }
        else
        {
            m->log = m->log.append(addLogPrefix("启动ffmpeg失败"));
            qDebug("启动ffmpeg失败");
            m->closeStream();
            QApplication::postEvent(m, new CustomeEvent(CustomeEvent::ID::OPEN_ERROR));
            return;
        }
    }

    QApplication::postEvent(m, new CustomeEvent(CustomeEvent::ID::CALL_SUCCESS));
}

/**
 * @brief MainWindow::stopCall
 * @param mainwindow
 * 停止通话 线程方法
 */
void MainWindow::stopCall(MainWindow *m)
{
    m->inputStream->closeInputStream();
    m->outputStream->CloseOutput();
    m->ffmpeg->toStop();
    m->ffmpeg->wait();//等待结束
    //成功关闭
    QApplication::postEvent(m, new CustomeEvent(CustomeEvent::ID::STOP_SUCCESS));
}

/**
 * @brief MainWindow::closeApplication
 * @param m
 *
 */
void MainWindow::closeApplication(MainWindow *m)
{
    m->inputStream->closeInputStream();
    m->outputStream->CloseOutput();
    m->ffmpeg->toStop();
    m->ffmpeg->wait();//等待结束
    QThread::msleep(5000);
    QApplication::postEvent(m, new CustomeEvent(CustomeEvent::ID::CLOSE_APP));
}

/**
 * @brief MainWindow::addLogPrefix
 * @param data
 * @return
 * QString添加时间前缀和 ‘\n’后缀
 */
QString MainWindow::addLogPrefix(QString data)
{
    return QTime::currentTime().toString("hh:mm:ss.zzz").append(" ").append(data).append("\n");
}

/**
 * @brief MainWindow::action_serverSet_slot
 */
void MainWindow::action_serverSet_slot()
{
    ServerSetDialog dialog(serverSetting.ip, serverSetting.ctrlPort, serverSetting.dataPort, this);
    dialog.setWindowTitle(tr("服务器的设置"));
    int ret = dialog.exec();
    if(ret == QDialog::Accepted)//按下了确定按钮
    {
        serverSetting.ip = dialog.getIp();
        serverSetting.ctrlPort = dialog.getCtrlPort().toInt();
        serverSetting.dataPort = dialog.getDataPort().toInt();
        qDebug("ServerSetDialog 点击确定");
    }
    else if(ret == QDialog::Rejected)//按下了取消按钮
    {
        qDebug() << tr("ServerSetDialog 点击取消");
    }
}

/**
 * @brief MainWindow::action_exit_slot
 */
void MainWindow::action_exit_slot()
{
    close();//触发closeEvent事件
}

/**
 * @brief MainWindow::action_font_slot
 */
void MainWindow::action_font_slot()
{
    QFontDialog dialog(this);
    int ret = dialog.exec();
    if(ret == QDialog::Accepted)
    {
        QFont font = dialog.selectedFont();
        qDebug() <<QString::fromUtf8("字体:") <<font.family()
                <<QString::fromUtf8("加粗:")<< font.bold()
               <<QString::fromUtf8("斜体:")<<font.italic();
    }
}

/**
 * @brief MainWindow::pushButton_call_slot
 * 拨号按钮被点击
 */
void MainWindow::pushButton_call_slot()
{
    QString text = ui->pushButton_call->text();
    if(ui->pushButton_call->isEnabled())
    {
        if(text=="拨号")
        {
            //设置固定大小
            setFixedSize(size());
            ui->pushButton_call->setText("挂断");
            ui->pushButton_call->setEnabled(false);
            QtConcurrent::run(MainWindow::startCall, this);
        }
        else if(text=="挂断")
        {
            ui->pushButton_call->setText("拨号");
            ui->pushButton_call->setEnabled(false);
            QtConcurrent::run(MainWindow::stopCall, this);
        }
    }
}

/**
 * @brief MainWindow::action_user_info_set_slot
 */
void MainWindow::action_user_info_set_slot()
{
    qDebug() <<tr("用户信息设置");
}

/**
 * @brief MainWindow::action_help_slot
 */
void MainWindow::action_help_slot()
{
    qDebug() <<tr("查看帮助");
}

/**
 * @brief MainWindow::action_about_slot
 */
void MainWindow::action_about_slot()
{
    qDebug() <<tr("关于");
}

/**
 * @brief MainWindow::action_collectionSet_slot
 */
void MainWindow::action_collectionSet_slot()
{
    CollectionSetDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted)
    {
        info.audioDeviceName = dialog.getAudioDeviceName();
        info.videoDeviceName = dialog.getVideoDeviceName();
        qDebug() << "video device:"<< info.audioDeviceName
                 << "\naudio device:"<< info.videoDeviceName;
    }
    else
    {
        qDebug() << tr("取消选择设备");
    }
}

/**
 * @brief MainWindow::action_log_slot
 * 日志对话框
 */
void MainWindow::action_log_slot()
{
    LogDialog l(this);
    l.setLog(log);
    l.exec();
}

void MainWindow::closeStream()
{
    inputStream->closeInputStream();
    outputStream->CloseOutput();
    ffmpeg->toStop();
    ffmpeg->wait();//等待结束
}

//void MainWindow::AudioCaptureCallback(AVStream *st, AVFrame *frame, int64_t lTimeStamp)
//{
//    outputStream->write_audio_frame(st, frame, lTimeStamp);
//}
//
//void MainWindow::VideoCaptureCallback(AVStream *st, AVPixelFormat format, AVFrame * frame, int64_t lTimeStamp)
//{
//    outputStream->write_video_frame(st, format, frame, lTimeStamp);
//}
