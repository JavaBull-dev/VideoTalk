#include "iffmpegaudio.h"
#include <QMutexLocker>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QDebug>

/**
 * @brief IFFmpegAudio::IFFmpegAudio
 * @param parent
 */
IFFmpegAudio::IFFmpegAudio(IFFmpeg* ffmpeg, QObject *parent) : QThread(parent)
{
    this->ffmpeg = ffmpeg;
    curTimestampSec = 0;
}

/**
 * @brief IFFmpegAudio::start
 */
void IFFmpegAudio::start(QThread::Priority priotity)
{
    qDebug() << "void IFFmpegAudio::start(QThread::Priority priotity)";
    QThread::start(priotity);
    canRun = true;
}

/**
 * @brief IFFmpegAudio::GetCurTimeSec
 * @return
 * 时间戳信息
 */
float IFFmpegAudio::getCurTimeSec() const
{
    return this->curTimestampSec;
}

/**
 * @brief IFFmpegAudio::run
 * 线程方法
 */
void IFFmpegAudio::run()
{
    qDebug("void IFFmpegAudio::run() : start");
    char buf[20000] = { 0 };

    const AudioParam* audioParam = ffmpeg->getAudioParam();
    QAudioFormat  fmt;                            // 设置音频输出格式
    fmt.setSampleRate(audioParam->sampleRate);                // 1秒的音频采样率
    fmt.setSampleSize(16);                        // 声音样本的大小
    fmt.setChannelCount(audioParam->channel);                 // 声道
    fmt.setCodec("audio/pcm");                    // 解码格式
    fmt.setByteOrder(QAudioFormat::LittleEndian);
    fmt.setSampleType(QAudioFormat::UnSignedInt); // 设置音频类型
	QAudioOutput* output = new QAudioOutput(fmt);//产生异常
    QIODevice* io = output->start();                         // 播放开始

    while (canRun)
    {
        if (output->bytesFree() > output->periodSize())
        {
            if(ffmpeg->audioList.list.size() > 0)
            {
                AVPacket pkt;
                {
                    QMutexLocker locker(&ffmpeg->audioList.mutex);
                    pkt = ffmpeg->audioList.list.takeFirst();
                    curTimestampSec = ffmpeg->getPts(&pkt);//获取音频时间戳信息
                }

                if(pkt.size<0)//结束
                {
                    av_packet_unref(&pkt);
                    canRun = false;
                    continue;
                }
                AVFrame *audioFrame = ffmpeg->decodePacket(&pkt); // 解码音频
                av_packet_unref(&pkt);                           // 释放pkt包
                int len = ffmpeg->convertToPcm(buf, audioFrame);
                if(len<0)
                {
                    av_frame_free(&audioFrame);
                    break;
                }
                av_frame_free(&audioFrame);
                io->write(buf, len);
            }
            else
            {
				//轮询次数过于频繁，会导致cpu占用率高
                msleep(1);
            }
        }
		else
		{
			//轮询次数过于频繁，会导致cpu占用率高
			msleep(1);
		}
    }

    io->close();
	output->stop();
	delete output;
    qDebug("void IFFmpegAudio::run() : end");
}

/**
 * @brief IFFmpegAudio::startProcessSlot
 * 通知启动
 */
void IFFmpegAudio::startProcessSlot()
{
    this->start();
}

/**
 * @brief IFFmpegAudio::toStop
 * 停止run执行
 */
void IFFmpegAudio::toStop()
{
    if(this->isRunning())
    {
        canRun = false;
    }
}
