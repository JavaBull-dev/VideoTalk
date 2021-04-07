#include "avinputstream.h"
#include <QtConcurrent>
#include <QFuture>

AVInputStream::AVInputStream(AVOutputStream* outputStream, QObject *parent)
    : QObject(parent)
{
    mExit = false;

    mVidFmtCtx = nullptr;
    mAudFmtCtx = nullptr;
    mInputFormat = nullptr;

    decPkt = nullptr;

    mVideoindex = -1;
    mAudioindex = -1;

    mStartTime = 0;
    this->outputStream = outputStream;

    av_register_all();
    avformat_network_init();
    avdevice_register_all();
}

AVInputStream::~AVInputStream()
{
    closeInputStream();
}

void  AVInputStream::setVideoCaptureDevice(QString device_name)
{
    videoDevice = device_name;
}

void  AVInputStream::setAudioCaptureDevice(QString device_name)
{
    audioDevice = device_name;
}

bool  AVInputStream::openInputStream()
{
    if(videoDevice.isEmpty() && audioDevice.isEmpty())
    {
        qDebug("you have not set any capture device");
        return false;
    }

    int i;

    //打开Directshow设备前需要调用FFmpeg的avdevice_register_all函数，否则下面返回失败
    mInputFormat = av_find_input_format("dshow");
    assert(mInputFormat != nullptr);

    // Set device params
    AVDictionary *device_param = 0;
	av_dict_set(&device_param, "rtbufsize", "30412800", 0);//默认大小3041280
    //if not setting rtbufsize, error messages will be shown in cmd, but you can still watch or record the stream correctly in most time
    //setting rtbufsize will erase those error messages, however, larger rtbufsize will bring latency
    //av_dict_set(&device_param, "rtbufsize", "10M", 0);

    if(!videoDevice.isEmpty())
    {
        int res = 0;

        QString device_name = "video=" + videoDevice;

         //Set own video device's name
        if ((res = avformat_open_input(&mVidFmtCtx, device_name.toUtf8().data(), mInputFormat, &device_param)) != 0)
        {
            qDebug("Couldn't open input video stream");
            return false;
        }
        //input video initialize
        if (avformat_find_stream_info(mVidFmtCtx, nullptr) < 0)
        {
            qDebug("Couldn't find video stream information");
            return false;
        }
        mVideoindex = -1;
        for (i = 0; i < mVidFmtCtx->nb_streams; i++)
        {
            if (mVidFmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
            {
                mVideoindex = i;
                break;
            }
        }

        if (mVideoindex == -1)
        {
            qDebug("Couldn't find a video stream.");
            return false;
        }
        if (avcodec_open2(mVidFmtCtx->streams[mVideoindex]->codec, avcodec_find_decoder(mVidFmtCtx->streams[mVideoindex]->codec->codec_id), nullptr) < 0)
        {
            qDebug("Could not open video codec.");
            return false;
        }
    }

    //////////////////////////////////////////////////////////

    if(!audioDevice.isEmpty())
    {
        QString device_name = "audio=" + audioDevice;

        //Set own audio device's name
        if (avformat_open_input(&mAudFmtCtx, device_name.toUtf8().data(), mInputFormat, &device_param) != 0)
        {
            qDebug("Couldn't open input audio stream.");
            return false;
        }

        //input audio initialize
        if (avformat_find_stream_info(mAudFmtCtx, nullptr) < 0)
        {
            qDebug("Couldn't find audio stream information");
            return false;
        }
        mAudioindex = -1;
        for (i = 0; i < mAudFmtCtx->nb_streams; i++)
        {
            if (mAudFmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
            {
                mAudioindex = i;
                break;
            }
        }
        if (mAudioindex == -1)
        {
            qDebug("Couldn't find a audio stream");
            return false;
        }
        if (avcodec_open2(mAudFmtCtx->streams[mAudioindex]->codec, avcodec_find_decoder(mAudFmtCtx->streams[mAudioindex]->codec->codec_id), nullptr) < 0)
        {
            qDebug("Could not open audio codec");
            return false;
        }
    }

    return true;
}

bool  AVInputStream::startCapture()
{
    if (mVideoindex == -1 && mAudioindex == -1)
    {
        qDebug("you can't open device");
        return false;
    }

    mStartTime = av_gettime();

    mExit = false;

    if(!videoDevice.isEmpty())
    {
        //启动video 采集线程
//        videocap = new std::thread(captureVideoThreadFunc, this);
        videocapResult = QtConcurrent::run(captureVideoThreadFunc, this);
    }

    if(!audioDevice.isEmpty())
    {
        //启动audio 采集线程
        audiocapResult = QtConcurrent::run(captureAudioThreadFunc, this);
//        audiocap = new std::thread(captureAudioThreadFunc, this);
    }

    return true;
}

/**
 * @brief AVInputStream::closeInputStream
 */
void  AVInputStream::closeInputStream()
{
    mExit = true;

//    if(videocap)
//    {
//        videocap->join();
//        videocap = nullptr;
//    }

//    if(audiocap)
//    {
//        audiocap->join();
//        audiocap = nullptr;
//    }
//    videocapResult.cancel();
//    audiocapResult.cancel();

    //等待线程停止
    videocapResult.waitForFinished();
    audiocapResult.waitForFinished();

     //关闭输入流
    if (mVidFmtCtx != nullptr)
    {
        avformat_close_input(&mVidFmtCtx);
    }
    if (mAudFmtCtx != nullptr)
    {
        avformat_close_input(&mAudFmtCtx);
    }

    if(mVidFmtCtx)
    {
        avformat_free_context(mVidFmtCtx);
    }
    if(mAudFmtCtx)
    {
        avformat_free_context(mAudFmtCtx);
    }

    mVidFmtCtx = nullptr;
    mAudFmtCtx = nullptr;
    mInputFormat = nullptr;

    mVideoindex = -1;
    mAudioindex = -1;
}

void AVInputStream::captureVideoThreadFunc(AVInputStream* a)
{
    //QThread::msleep(10);
    a->readVideoPackets();
}

int  AVInputStream::readVideoPackets()
{
    if(decPkt == nullptr)
    {
        ////prepare before decode and encode
        decPkt = (AVPacket *)av_malloc(sizeof(AVPacket));
    }

    int encode_video = 1;
    int ret;

    //start decode and encode

    while (encode_video)
    {
        if (mExit)
            break;

        AVFrame * pframe = nullptr;
        if ((ret = av_read_frame(mVidFmtCtx, decPkt)) >= 0)
        {
            pframe = av_frame_alloc();
            if (!pframe)
            {
                ret = AVERROR(ENOMEM);
                return ret;
            }
            int dec_got_frame = 0;
            ret = avcodec_decode_video2(mVidFmtCtx->streams[decPkt->stream_index]->codec,
                pframe, &dec_got_frame, decPkt);
            if (ret < 0)
            {
                av_frame_free(&pframe);
                qDebug("video decode error");
                break;
            }
            if (dec_got_frame)
            {
                outputStream->write_video_frame(mVidFmtCtx->streams[decPkt->stream_index],
                        mVidFmtCtx->streams[mVideoindex]->codec->pix_fmt,
                    pframe, av_gettime() - mStartTime);

                av_frame_free(&pframe);
            }
            else
            {
                av_frame_free(&pframe);
            }

            av_free_packet(decPkt);
        }
        else
        {
            if (ret == AVERROR_EOF)
                encode_video = 0;
            else
            {
                qDebug("Could not read video frame");
                break;
            }
        }
    }

    return 0;
}

/**
 * @brief AVInputStream::captureAudioThreadFunc
 * @param a
 * 线程方法
 */
void AVInputStream::captureAudioThreadFunc(AVInputStream* a)
{
    //QThread::msleep(10);
    a->readAudioPackets();
}

int AVInputStream::readAudioPackets()
{
    //audio trancoding here
    int ret;

    int encode_audio = 1;
    int dec_got_frame_a = 0;

    //start decode and encode
    while (encode_audio)
    {
        if (mExit)
           break;

        /**
        * Decode one frame worth of audio samples, convert it to the
        * output sample format and put it into the FIFO buffer.
        */
        AVFrame *input_frame = av_frame_alloc();
        if (!input_frame)
        {
            ret = AVERROR(ENOMEM);
            return ret;
        }

        /** Decode one frame worth of audio samples. */
        /** Packet used for temporary storage. */
        AVPacket input_packet;
        av_init_packet(&input_packet);
        input_packet.data = nullptr;
        input_packet.size = 0;

        /** Read one audio frame from the input file into a temporary packet. */
        if ((ret = av_read_frame(mAudFmtCtx, &input_packet)) < 0)
        {
            /** If we are at the end of the file, flush the decoder below. */
            if (ret == AVERROR_EOF)
            {
                encode_audio = 0;
            }
            else
            {
                qDebug("Could not read audio frame");
                return ret;
            }
        }

        /**
        * Decode the audio frame stored in the temporary packet.
        * The input audio stream decoder is used to do this.
        * If we are at the end of the file, pass an empty packet to the decoder
        * to flush it.
        */
        if ((ret = avcodec_decode_audio4(mAudFmtCtx->streams[mAudioindex]->codec,
                                         input_frame, &dec_got_frame_a, &input_packet)) < 0)
        {
            qDebug("Could not decode audio frame");
            return ret;
        }
        av_packet_unref(&input_packet);
        /** If there is decoded data, convert and store it */
        if (dec_got_frame_a)
        {
//            if(m_pAudioCBFunc)
            {
//                CAutoLock lock(&m_WriteLock);
//                m_pAudioCBFunc(mAudFmtCtx->streams[mAudioindex], input_frame, av_gettime() - mStartTime);
//                emit AudioCaptureCallback(mAudFmtCtx->streams[mAudioindex],
//                                          input_frame, av_gettime() - mStartTime);
                outputStream->write_audio_frame(mAudFmtCtx->streams[mAudioindex],
                                                 input_frame, av_gettime() - mStartTime);
            }
        }

        av_frame_free(&input_frame);
    }

    return 0;
}

bool AVInputStream::getVideoInputInfo(int & width, int & height, int & frame_rate, AVPixelFormat & pixFmt)
{
    if(mVideoindex != -1)
    {
        width  =  mVidFmtCtx->streams[mVideoindex]->codec->width;
        height =  mVidFmtCtx->streams[mVideoindex]->codec->height;

        AVStream *stream = mVidFmtCtx->streams[mVideoindex];

        pixFmt = stream->codec->pix_fmt;

        //frame_rate = stream->avg_frame_rate.num/stream->avg_frame_rate.den;//每秒多少帧

        if(stream->r_frame_rate.den > 0)
        {
          frame_rate = stream->r_frame_rate.num/stream->r_frame_rate.den;
        }
        else if(stream->codec->framerate.den > 0)
        {
          frame_rate = stream->codec->framerate.num/stream->codec->framerate.den;
        }

        return true;
    }
    return false;
}

bool  AVInputStream::getAudioInputInfo(AVSampleFormat & sample_fmt, int & sample_rate, int & channels)
{
    if(mAudioindex != -1)
    {
        sample_fmt = mAudFmtCtx->streams[mAudioindex]->codec->sample_fmt;
        sample_rate = mAudFmtCtx->streams[mAudioindex]->codec->sample_rate;
        channels = mAudFmtCtx->streams[mAudioindex]->codec->channels;

        return true;
    }
    return false;
}
