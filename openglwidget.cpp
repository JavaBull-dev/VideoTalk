#include "openglwidget.h"
#include <QPainter>
#include <QDebug>

/**
 * @brief OpenGLWidget::OpenGLWidget
 * @param ffmpegVideo
 * @param ffmpeg
 * @param parent
 */
OpenGLWidget::OpenGLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{
}

/**
 * @brief OpenGLWidget::paintEvent
 * @param event
 * 渲染rgba
 */
void OpenGLWidget::paintEvent(QPaintEvent *event)
{
    if(ffmpegVideo && ffmpeg)
    {
        QList<AVFrame*>* frameList = ffmpegVideo->getFrameList();

        if (frameList->size() > 0)
        {
            AVFrame* frame = frameList->takeFirst();
            QSize openglWidgetSize = size();
            int ret =ffmpeg->convertToRGB(frame,
                (char *)image->bits(),
                openglWidgetSize.width(),
                openglWidgetSize.height());

            av_frame_free(&frame);

            if(ret<0)
            {
                qDebug("void OpenGLWidget::paintEvent(QPaintEvent *event) : "
                       "error convertToRGB");
                return ;
            }

            QPainter painter;                                // 画板
            painter.begin(this);
            painter.drawImage(QPoint(0, 0), *image);
            painter.end();
        }
    }
}

/**
 * @brief OpenGLWidget::timerEvent
 * @param event
 */
void OpenGLWidget::timerEvent(QTimerEvent *event)
{
    update();
}

/**
 * @brief OpenGLWidget::resizeGL
 * @param w
 * @param h
 * 窗口大小变化
 */
void OpenGLWidget::resizeGL(int w, int h)
{
//    qDebug("w=%d, h=%d", w, h);
//    qDebug() << "minsize:"<< minimumSize() << "maxsize:"<< maximumSize();
//    qDebug()<< size();
}

/**
 * @brief OpenGLWidget::initParam
 * 初始化视频渲染所需要的参数
 */
void OpenGLWidget::initParamSlot(IFFmpeg* ffmpeg, FFmpegVideo* ffmpegVideo)
{
    QSize si = size();
    int width = si.width();
    int height = si.height();

    if (buf)
    {
        delete buf;
    }
    buf = new uchar[width * height * 4];

    if (image)
    {
        delete image;
    }
    image = new QImage(buf, width, height, QImage::Format_ARGB32);
    //赋值
    this->ffmpeg = ffmpeg;
    this->ffmpegVideo = ffmpegVideo;
    qDebug("void OpenGLWidget::initParamSlot(IFFmpeg* ffmpeg, FFmpegVideo* ffmpegVideo) : "
           "frameWidth=%d frameHeight=%d", width, height);

    //启动定时器
    timerId = startTimer(timeInterval);
    if(timerId == 0)
    {
        qDebug("void OpenGLWidget::initParamSlot(IFFmpeg* ffmpeg, FFmpegVideo* ffmpegVideo) : "
               "can not start a timer");
    }
}

/**
 * @brief OpenGLWidget::destoryParam
 * 清除参数
 */
void OpenGLWidget::destoryParamSlot()
{
    if(timerId!=-1)
    {
        killTimer(timerId);
        timerId = -1;
    }

    if (buf)
    {
        delete buf;
        buf = nullptr;
    }
    if (image)
    {
        delete image;
        image = nullptr;
    }

    this->ffmpegVideo = nullptr;
    this->ffmpeg = nullptr;
    qDebug("void OpenGLWidget::destoryParamSlot()");
}
