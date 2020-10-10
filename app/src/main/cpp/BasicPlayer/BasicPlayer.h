#pragma once

#include <string>
#include "BasicQueue/BasicQueue.h"
#include "BasicAV/BasicAV.h"
#include "BasicThread/BasicThread.h"

enum DecoderType {
    DECODER_TYPE_VIDEO = 0,
    DECODER_TYPE_AUDIO = 1
};

enum PlayerStatusCtr {
    VPLAYER_CTR_STATUS_PLAYING = 1,
    VPLAYER_CTR_STATUS_PAUSEING = 0
};

class BasicPlayerController : public BasicThread {
public:
    BasicPlayerController(std::string path, double _seekTime = 0.0);

    ~BasicPlayerController();

    virtual void run();

    int Play();

    int Pause();

    int GetVideoQueueSize();

    int GetAudioQueueSize();

    int PushFrameToVideoQueue(BasicAVFrame *frame);

    int PushFrameToAudioQueue(BasicAVFrame *frame);

private:
    BasicQueue<BasicAVFrame> videoQueue;
    BasicQueue<BasicAVFrame> audioQueue;

    PlayerStatusCtr status = PlayerStatusCtr::VPLAYER_CTR_STATUS_PLAYING;

    std::string path;
    double seekTime = 0.0;
};

class BasicPlayerReaderThread : public BasicThread {
public:
    BasicPlayerReaderThread(std::string path, double seekTime, BasicPlayerController *playerCtr);

    ~BasicPlayerReaderThread();

    virtual void run();

private:
    std::string path;
    BasicPlayerController *playerCtr = nullptr;

    double seekTime = 0.0;
};

class BasicPlayerDecoderThread : public BasicThread {
public:
    BasicPlayerDecoderThread(BasicPlayerController *playerCtr, DecoderType type);

    ~BasicPlayerDecoderThread();

    virtual void run();

    int Init(BasicAVStream *avStream);

    int PutPacket(BasicAVPacket *pkt);

    int GetPacketQueueSize();

private:
    BasicAVDecoder *decoder = nullptr;
    BasicQueue<BasicAVPacket> packetQueue;

    BasicPlayerController *playerCtr = nullptr;
    DecoderType type;
};

class BasicPlayer {
public:
    BasicPlayer(std::string path);

    ~BasicPlayer();

    int Open(double time = 0.0);

    int Stop();

    int Play();

    int Pause();

    int Seek(double time);


private:
    std::string path;
    BasicPlayerReaderThread *readerThread = nullptr;

    BasicPlayerController *playerCtr = nullptr;
};