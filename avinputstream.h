#ifndef AVINPUTSTREAM_H
#define AVINPUTSTREAM_H

#include <QObject>
extern "C"
{
#include "libavutil/opt.h"
#include "libavutil/channel_layout.h"
#include "libavutil/common.h"
#include "libavutil/imgutils.h"
#include "libavutil/mathematics.h"
#include "libavutil/samplefmt.h"
#include "libavutil/time.h"
#include "libavutil/fifo.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavformat/avio.h"
#include "libavfilter/avfilter.h"
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libavdevice/avdevice.h"
}
#include <thread>
#include <QThread>
#include "avoutputstream.h"
#include <QFuture>
//#include "captureaudiothread.h"
//#include "capturevideothread.h"

class AVInputStream : public QObject
{
    Q_OBJECT
public:
    explicit AVInputStream(AVOutputStream* outputStream, QObject *parent = nullptr);
    ~AVInputStream();

    void  setVideoCaptureDevice(QString device_name);
    void  setAudioCaptureDevice(QString device_name);

    bool  openInputStream();
    void  closeInputStream();

    bool  startCapture();

    bool  getVideoInputInfo(int & width, int & height, int & framerate, AVPixelFormat & pixFmt);
    bool  getAudioInputInfo(AVSampleFormat & sample_fmt, int & sample_rate, int & channels);

    int  readVideoPackets();
    int  readAudioPackets();

protected:
    static void captureAudioThreadFunc(AVInputStream* a);
    static void captureVideoThreadFunc(AVInputStream* a);

protected:
    QString  videoDevice;
    QString  audioDevice;

    int     mVideoindex;
    int     mAudioindex;

    AVFormatContext *mVidFmtCtx;
    AVFormatContext *mAudFmtCtx;
    AVInputFormat  *mInputFormat;

    AVPacket *decPkt;

    bool   mExit; //退出线程的标志变量

    int64_t     mStartTime; //采集的起点时间

//    std::thread* videocap = nullptr;//视频采集线程
//    std::thread* audiocap = nullptr;//音频采集线程
    QFuture<void> videocapResult;
    QFuture<void> audiocapResult;

//    CaptureAudioThread* audiocap = nullptr;
//    CaptureVideoThread* videocap = nullptr;

    AVOutputStream* outputStream;
signals:
//    void VideoCaptureCallback(AVStream * input_st, enum AVPixelFormat pix_fmt,
//                              AVFrame *pframe, int64_t lTimeStamp);
//    void AudioCaptureCallback(AVStream * input_st, AVFrame *pframe,
//                              int64_t lTimeStamp);
public slots:
};

#endif // AVINPUTSTREAM_H
