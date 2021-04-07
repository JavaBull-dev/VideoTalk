#include "ffmpegvideo.h"
#include <QDebug>

FFmpegVideo::FFmpegVideo(IFFmpeg* ffmpeg, IFFmpegAudio* ffmpegAudio, QObject *parent)
    : QThread(parent)
{
    this->ffmpeg = ffmpeg;
    this->ffmpegAudio = ffmpegAudio;
}

/**
 * @brief FFmpegVideo::start
 * @param priority
 */
void FFmpegVideo::start(QThread::Priority priority)
{
    qDebug() << "void FFmpegVideo::start(QThread::Priority)";
    canRun = true;
    QThread::start(priority);
}

/**
 * @brief FFmpegVideo::getFrameList
 * @return
 */
QList<AVFrame *> *FFmpegVideo::getFrameList()
{
    return &frameList;
}

/**
 * @brief FFmpegVideo::run
 */
void FFmpegVideo::run()
{
    qDebug() << "void FFmpegVideo::run() : start";
    emit initParamSignal(ffmpeg, this);

    while (canRun)
    {
        if (ffmpeg->videoList.list.size() > 0)
        {
            AVPacket pkt;
            {
                QMutexLocker locker(&ffmpeg->videoList.mutex);
                pkt = ffmpeg->videoList.list.takeFirst();
            }

            if(pkt.size<0)
            {
                av_packet_unref(&pkt);
                canRun = false;
                break;
            }
            curTimestampSec = ffmpeg->getPts(&pkt);

            // curTimestampSec > ffmpegAudio->getCurTimeSec()
            while (canRun && (curTimestampSec > ffmpegAudio->getCurTimeSec()))
            {
                msleep(1);
                if(!ffmpegAudio->isRunning())
                {
                    canRun = false;
                    break;
                }
            }
            AVFrame *videoFrame = ffmpeg->decodePacket(&pkt); // 解码
            av_packet_unref(&pkt);//释放资源

            //限制frameList的大小
//            while(frameList.size()>=maxlen)
//            {
//                QThread::msleep(1);
//            }
            frameList.append(videoFrame);//frame list, 将数据交给OpenGLWidget
        }
        else
        {
            QThread::msleep(1);
        }
    }

    emit destoryParamSignal();
    qDebug() << "void FFmpegVideo::run() : end";
}

/**
 * @brief FFmpegVideo::startProcessSlot
 */
void FFmpegVideo::startProcessSlot()
{
    this->start();
}
