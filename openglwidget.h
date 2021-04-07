#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QResizeEvent>
#include <QMutex>
#include <QImage>
#include "ffmpegvideo.h"
#include "iffmpeg.h"

class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event); // 窗口的重新绘制
    void timerEvent(QTimerEvent *event); // 定时器事件处理函数
protected:
//    void resizeEvent(QResizeEvent *event);
    void resizeGL(int w, int h);
private:
    int timerId = -1;
    QImage *image = nullptr;
    uchar *buf = nullptr;
    int timeInterval = 30;
    FFmpegVideo* ffmpegVideo = nullptr;
    IFFmpeg* ffmpeg = nullptr;
signals:

public slots:
    void initParamSlot(IFFmpeg* ffmpeg, FFmpegVideo* ffmpegVideo);
    void destoryParamSlot();
};

#endif // OPENGLWIDGET_H
