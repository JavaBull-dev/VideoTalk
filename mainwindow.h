#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QResizeEvent>
#include "iffmpeg.h"
#include "iffmpegaudio.h"
#include "ffmpegvideo.h"
#include "avinputstream.h"
#include "avoutputstream.h"

namespace Ui {
class MainWindow;
}

typedef struct
{
    QString ip;
    int ctrlPort;
    int dataPort;
} SererSetting;

typedef struct
{
    QString nick;
    QString number;
} UserInfoSetting;

typedef struct
{
    QString videoDeviceName;
    QString audioDeviceName;
} DeviceInfo;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
    bool event(QEvent *event);

private:
    SererSetting serverSetting;
    UserInfoSetting userSetting;
    IFFmpeg* ffmpeg;
    IFFmpegAudio* ffmpegAudio;
    FFmpegVideo* ffmpegVideo;
    int winMaxSize;
    int winMinSize;
    QString cameraName;
    DeviceInfo info;
    AVInputStream* inputStream;
    AVOutputStream* outputStream;

    static void startCall(MainWindow* m);
    static void stopCall(MainWindow* m);
    static void closeApplication(MainWindow* m);
    static QString addLogPrefix(QString data);

private slots:
    void action_serverSet_slot();
    void action_exit_slot();
    void action_font_slot();
    void pushButton_call_slot();
    void action_user_info_set_slot();
    void action_help_slot();
    void action_about_slot();
    void action_collectionSet_slot();
    void action_log_slot();
//    void AudioCaptureCallback(AVStream* st, AVFrame* frame, int64_t lTimeStamp);
//    void VideoCaptureCallback(AVStream* st, enum AVPixelFormat format,AVFrame* frame, int64_t lTimeStamp);

private:
    Ui::MainWindow *ui;
    QString log;

    void closeStream();
};

#endif // MAINWINDOW_H
