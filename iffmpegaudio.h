#ifndef IFFMPEGAUDIO_H
#define IFFMPEGAUDIO_H

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

class IFFmpegAudio : public QThread
{
    Q_OBJECT
public:
    explicit IFFmpegAudio(IFFmpeg* ffmpeg, QObject *parent = nullptr);
    void start(Priority = InheritPriority);
    float getCurTimeSec() const;
protected:
    void run();
private:
    bool canRun = true;
    IFFmpeg* ffmpeg;
    float curTimestampSec = -1;
    int  convertToPcm(char* buf, AVFrame* audioFrame);
signals:

public slots:
    void startProcessSlot();
    void toStop();
};

#endif // IFFMPEGAUDIO_H
