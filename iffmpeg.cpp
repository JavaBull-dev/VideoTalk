#include "iffmpeg.h"
#include <QDebug>

/**
 * @brief IFFmpeg::IFFmpeg
 * @param parent
 * ffmpeg 注册组件
 */
IFFmpeg::IFFmpeg(QObject *parent) : QThread(parent)
{
    av_register_all();
    avformat_network_init();
    videoParam.index = -1;
    audioParam.index = -1;
}

/**
 * @brief IFFmpeg::start
 * @param priority
 */
void IFFmpeg::start(QThread::Priority priority)
{
    qDebug() <<"void IFFmpeg::start(QThread::Priority priority)";
    canRun = true;
    QThread::start(priority);
}

/**
 * @brief IFFmpeg::openStream
 * @param url
 * @return
 * 初始化输入
 */
int IFFmpeg::openStream(QString url)
{
    release();

    if (url.isEmpty())
    {
        return -1;
    }

    QMutexLocker locker(&mutex);
    fmtCtx = avformat_alloc_context();

    int ret = 0;

    if ((ret = avformat_open_input(&fmtCtx, url.toLocal8Bit().data(), nullptr, nullptr)) < 0) {
        qDebug() << "int IFFmpeg::openStream(QString url) : avformat_open_input error";
        return ret;
    }

    if ((ret = avformat_find_stream_info(fmtCtx, nullptr)) < 0) {
        qDebug() << "int IFFmpeg::openStream(QString url) : avformat_find_stream_info error";
        return -1;
    }

    for (int i = 0; i < fmtCtx->nb_streams; i++)
    {
        AVCodecContext *codecCtx = fmtCtx->streams[i]->codec;

        if (codecCtx->codec_type == AVMEDIA_TYPE_VIDEO)           // 判断是否为视频
        {
            videoParam.index = i;

            AVCodec *codec = avcodec_find_decoder(codecCtx->codec_id); // 查找解码器
            if (!codec)                                           // 未找到解码器
            {
                qDebug() << "int IFFmpeg::openStream(QString url) : avcodec_find_decoder error";
                return -1;
            }

            int err = avcodec_open2(codecCtx, codec, nullptr); // 打开解码器
            if (err != 0)
            {
                qDebug() << "int IFFmpeg::openStream(QString url) : avcodec_find_decoder error";
                return -1;
            }
            videoParam.width = codecCtx->width;
            videoParam.height = codecCtx->height;
            qDebug("int IFFmpeg::openStream(QString url) : "
                   "open codec success, video width=%d, height=%d\n",
                codecCtx->width,
                codecCtx->height);
        }
        else if (codecCtx->codec_type == AVMEDIA_TYPE_AUDIO)         // 若未音频流
        {
            audioParam.index = i;                                      // 音频流
            AVCodec *codec = avcodec_find_decoder(codecCtx->codec_id); // 查找解码器

            if (avcodec_open2(codecCtx, codec, nullptr) < 0)
            {
                return -1;
            }

            audioParam.sampleRate = codecCtx->sample_rate; // 样本率
            audioParam.channel = codecCtx->channels;        // 通道数

            //每一个采样标本的大小
            switch (codecCtx->sample_fmt)                   // 样本大小
            {
            case AV_SAMPLE_FMT_S16:                    // signed 16 bits
                audioParam.sampleFmt = 16;
                break;

            case  AV_SAMPLE_FMT_S32: // signed 32 bits
                audioParam.sampleFmt = 32;

            default:
                audioParam.sampleFmt = codecCtx->sample_fmt;
                break;
            }

            qDebug("int IFFmpeg::openStream(QString url) : "
                   "audio sample rate:%d sample size:%d chanle:%d\n",
                audioParam.sampleRate,
                audioParam.sampleFmt,
                audioParam.channel);
        }
    }

    //初始化音频转换器
    AVCodecContext *ctx = fmtCtx->streams[audioParam.index]->codec;
    swrCtx = swr_alloc();
    swr_alloc_set_opts(swrCtx,
        ctx->channel_layout, // 输出的声道布局
        AV_SAMPLE_FMT_S16,   // 输出的样本格式
        ctx->sample_rate,    // 输出的采样率
        ctx->channel_layout, // 输入的声道布局
        ctx->sample_fmt,     // 输入的样本格式
        ctx->sample_rate,    // 输入的采样率
        0, nullptr);
    swr_init(swrCtx);

    return ret;
}

/**
 * @brief IFFmpeg::readPacket
 * @return
 * 从流中读取packet
 */
AVPacket IFFmpeg::readPacket()
{
    AVPacket pkt;

    memset(&pkt, 0, sizeof(AVPacket));

    int err = av_read_frame(fmtCtx, &pkt); // 读取帧

    if (err != 0)                              // 读取失败
    {
        pkt.size = -1;
    }

    return pkt;
}

/**
 * @brief IFFmpeg::decodePacket
 * @param pkt
 * @return
 * 解码视音频packet
 */
AVFrame *IFFmpeg::decodePacket(AVPacket *pkt)
{
    if (!fmtCtx)
    {
        return nullptr;
    }

    AVFrame* frame = av_frame_alloc();

    AVCodecContext* codecCtx = fmtCtx->streams[pkt->stream_index]->codec;

    int ret = avcodec_send_packet(codecCtx, pkt);

    if (ret != 0)
    {
        return nullptr;
    }

    ret = avcodec_receive_frame(codecCtx, frame);

    if (ret != 0)
    {
        //释放frame
        av_frame_unref(frame);
        return nullptr;
    }

    return frame;
}

/**
 * @brief IFFmpeg::convertToPcm
 * @param buf
 * @param audioFrame
 * @return
 */
int IFFmpeg::convertToPcm(char *buf, AVFrame *audioFrame)
{
    if (!fmtCtx || !audioFrame || !buf)
    {
        return -1;
    }
    AVCodecContext* codecCtx = fmtCtx->streams[audioParam.index]->codec; // 音频解码器上下文

    uint8_t *data[1];
    data[0] = (uint8_t *)buf;

    int len =swr_convert(swrCtx, data, audioFrame->nb_samples,
                         (const uint8_t **)audioFrame->data, audioFrame->nb_samples);

    if (len <= 0)
    {
        return -1;
    }

    // out_buffer_size = len * ctx->channels *
    // av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);
    return av_samples_get_buffer_size(nullptr,
        codecCtx->channels,
        audioFrame->nb_samples,
        AV_SAMPLE_FMT_S16,0);
}

const AudioParam *IFFmpeg::getAudioParam() const
{
    return &audioParam;
}

/**
 * @brief IFFmpeg::getPts
 * @param packet
 * @return
 * 计算显示时间戳
 */
float IFFmpeg::getPts(AVPacket *packet)
{
    return packet->pts * av_q2d(fmtCtx->streams[packet->stream_index]->time_base);
}

/**
 * @brief IFFmpeg::convertToRGB
 * @return
 * yuv转化为GBG
 */
int IFFmpeg::convertToRGB(const AVFrame *yuv, char *out, int outwidth, int outheight)
{
    if(!fmtCtx)
    {
        qDebug("int IFFmpeg::convertToRGB(const AVFrame *yuv, char *out, i"
               "nt outwidth, int outheight) : "
               "fmtCtx can't init");
        return -1;
    }

    AVCodecContext* codecCtx = fmtCtx->streams[videoParam.index]->codec;

    swsCtx = sws_getCachedContext(swsCtx, codecCtx->width, // 初始化一个SwsContext
        codecCtx->height,
        codecCtx->pix_fmt,     // 输入像素格式
        outwidth, outheight,
        AV_PIX_FMT_BGRA,       // 输出像素格式
        SWS_BICUBIC,           // 转码的算法
        nullptr, nullptr, nullptr);

    if (!swsCtx)
    {
        qDebug("int IFFmpeg::convertToRGB(const AVFrame *yuv, char *out, "
               "int outwidth, int outheight) :"
               "sws_getCachedContext error.");
        return -1;
    }

    uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };
    data[0] = (uint8_t *)out;
    int linesize[AV_NUM_DATA_POINTERS] = { 0 };

    linesize[0] = outwidth * 4;            // 一行的宽度，32位4个字节
    sws_scale(swsCtx, yuv->data,     // 当前处理区域的每个通道数据指针
        yuv->linesize,       // 每个通道行字节数
        0, codecCtx->height, // 原视频帧的高度
        data,                // 输出的每个通道数据指针
        linesize             // 每个通道行字节数
    );                   // 开始转码

    return 0;
}

/**
 * @brief IFFmpeg::toStop
 */
void IFFmpeg::toStop()
{
    canRun = false;
}

/**
 * @brief IFFmpeg::run
 * 线程方法
 */
void IFFmpeg::run()
{
    qDebug("void IFFmpeg::run() : start");
    if(fmtCtx)
    {
        //防止openStream()和start()同时运行
//        QMutexLocker locker(&mutex);
        //run ffmpegVideo ffmpegAudio
        emit startProcessSignal();

        while (canRun)
        {
            if ((videoList.list.size() > maxlen) &&(audioList.list.size() > maxlen))
            {
                QThread::msleep(20);
                //todo检查ffmpegVideo ffmpegAudio是否启动
                continue;
            }
            {
                AVPacket pkt = readPacket(); // 读取视频帧

                if (pkt.size < 0)      // 未打开视频
                {
                    qDebug() << "void IFFmpeg::run() : pkt.size < 0";
                    canRun = false;
                    av_packet_unref(&pkt);
                    continue;
                }

                if (pkt.stream_index == audioParam.index)
                {
                    QMutexLocker locker(&audioList.mutex);
                    audioList.list.append(pkt);
//                    qDebug() << "void IFFmpeg::run() : append audio packet --"<< audioList.list.size();
                }
                else if (pkt.stream_index == videoParam.index)
                {
                    QMutexLocker locker(&videoList.mutex);
                    videoList.list.append(pkt);
//                    qDebug() << "void IFFmpeg::run() : append video packet --"<< videoList.list.size();
                }
            }
        }

        AVPacket packet = *(av_packet_alloc());
        packet.size = -1;
        {
            QMutexLocker locker(&audioList.mutex);
            audioList.list.append(packet);
        }
        {
            QMutexLocker locker(&videoList.mutex);
            videoList.list.append(packet);
        }

        QThread::msleep(2000);
    }

    qDebug("void IFFmpeg::run() : end");
}

/**
 * @brief IFFmpeg::release
 * run() 方法快要结束时，释放申请的资源
 * avformat_alloc_context()
 */
void IFFmpeg::release()
{
    {
        QMutexLocker locker(&videoList.mutex);
        while (videoList.list.size()>0)
        {
           AVPacket packet = videoList.list.takeFirst();
           av_packet_unref(&packet);
        }
    }

    {
        QMutexLocker locker(&audioList.mutex);
        while (videoList.list.size()>0)
        {
           AVPacket packet = videoList.list.takeFirst();
           av_packet_unref(&packet);
        }
    }

    if(fmtCtx)
    {
        if(videoParam.index!=-1)
        {
            avcodec_close(fmtCtx->streams[videoParam.index]->codec);
        }
        if(audioParam.index!=-1)
        {
            avcodec_close(fmtCtx->streams[audioParam.index]->codec);
        }
        avformat_close_input(&fmtCtx);
        avformat_free_context(fmtCtx);
        fmtCtx = nullptr;
    }

    videoParam.index = -1;
    audioParam.index = -1;

    if(swrCtx)
    {
        swr_free(&swrCtx);
        swrCtx = nullptr;
    }

    if(swsCtx)
    {
        sws_freeContext(swsCtx);
        swsCtx = nullptr;
    }

    qDebug("void IFFmpeg::release() : release resource");
}
