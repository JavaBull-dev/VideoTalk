#ifndef FFMPEGVIDEO_H
#define FFMPEGVIDEO_H

#include <QThread>

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
#include "iffmpeg.h"
#include "iffmpegaudio.h"
#include <QList>

class FFmpegVideo : public QThread
{
    Q_OBJECT
public:
    explicit FFmpegVideo(IFFmpeg* ffmpeg, IFFmpegAudio* ffmpegAudio, QObject *parent = nullptr);
    void start(Priority = InheritPriority);
    QList<AVFrame*>* getFrameList();
protected:
    void run();
private:
    bool canRun;
    IFFmpeg* ffmpeg;
    IFFmpegAudio* ffmpegAudio;
    float curTimestampSec = 0.0;
    QList<AVFrame*> frameList;
    const int maxlen = 10;
signals:
    void initParamSignal(IFFmpeg* ffmpeg, FFmpegVideo* ffmpegVideo);
    void destoryParamSignal();
public slots:
    void startProcessSlot();
};

#endif // FFMPEGVIDEO_H
