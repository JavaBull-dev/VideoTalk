#ifndef IFFMPEG_H
#define IFFMPEG_H

#include <QThread>
#include <QMutex>

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
}

typedef struct
{
    QList<AVPacket>list;
    QMutex mutex;
} AVList;

typedef struct
{
    int index;
    int sampleRate; // 样本率
    int channel;
    int sampleFmt;
    float curPlaySec;
} AudioParam;

typedef struct
{
    int index;
    int width;
    int height;
} VideoParam;

/**
 * @brief The IFFmpeg class
 * 处理输入的ffmpeg
 */
class IFFmpeg : public QThread
{
    Q_OBJECT
public:
    explicit IFFmpeg(QObject *parent = nullptr);
    void start(Priority = InheritPriority);
    int openStream(QString url);
    AVPacket readPacket();
    AVFrame* decodePacket(AVPacket *pkt);
    int convertToPcm(char* buf, AVFrame* audioFrame);
    const AudioParam* getAudioParam() const;
    float getPts(AVPacket* packet);
    int convertToRGB(const AVFrame *yuv, char *out, int outwidth, int outheight);
    void toStop();
    const int maxlen = 5;
    AVList videoList;
    AVList audioList;
protected:
    void run();
private:
    bool canRun = true;
    QMutex mutex;
    AVFormatContext* fmtCtx = nullptr;
    VideoParam videoParam;
    AudioParam audioParam;
    SwrContext* swrCtx = nullptr;
    SwsContext* swsCtx = nullptr;
    QMutex resMutex;
    void release();
signals:
    void startProcessSignal();
public slots:
};

#endif // IFFMPEG_H
