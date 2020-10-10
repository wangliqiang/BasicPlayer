#pragma once

class BasicAVStreamPrivate;

class BasicAVStream;

class BasicAVPacketPrivate;

class BasicAVPacket {
public:
    BasicAVPacket();

    ~BasicAVPacket();

    int GetIndex();

public:
    BasicAVPacketPrivate *imp = nullptr;
};

class BasicAVFramePrivate;

class BasicAVFrame {
public:
    BasicAVFrame();

    ~BasicAVFrame();

    long long GetPts();

    int VideoPrint();

    int AudioPrint();

    int GetW();

    int GetH();

    int GetY(unsigned char *y);

    int GetU(unsigned char *u);

    int GetV(unsigned char *v);

public:
    BasicAVFramePrivate *imp = nullptr;
};

class BasicAVReaderPrivate;

class BasicAVReader {
public:
    BasicAVReader();

    ~BasicAVReader();

    int Open(char const *path);

    int GetStreamCount();

    int GetStream(BasicAVStream *stream, int streamId);

    int GetVideoStreamIndex();

    int GetAudioStreamIndex();

    int Close();

    int Read(BasicAVPacket *packet);

    int Seek(double time);

private:
    BasicAVReaderPrivate *imp = nullptr;


};

class BasicAVStream {
public:
    BasicAVStream();

    ~BasicAVStream();

public:
    int streamIndex = -1;

    int timebaseNum = 0;
    int timebaseDen = 0;

    BasicAVStreamPrivate *imp = nullptr;
};


class BasicAVDecoderPrivate;

class BasicAVDecoder {
public:
    BasicAVDecoder();

    ~BasicAVDecoder();

    int Init(BasicAVStream *stream);

    int SendPacket(BasicAVPacket *packet);

    int RecvFrame(BasicAVFrame *frame);

    int Close();

public:
    BasicAVDecoderPrivate *imp = nullptr;

    int timebaseNum = 0;
    int timebaseDen = 0;
};

class BasicAVTime {
public:
    static long long GetTime();
};