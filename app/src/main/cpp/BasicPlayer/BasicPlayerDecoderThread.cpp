#include "BasicPlayer.h"

BasicPlayerDecoderThread::BasicPlayerDecoderThread(BasicPlayerController *_playerCtr,
                                                   DecoderType _type) {
    decoder = new BasicAVDecoder();
    playerCtr = _playerCtr;
    type = _type;
}

BasicPlayerDecoderThread::~BasicPlayerDecoderThread() {
    if (decoder != nullptr) {
        delete decoder;
        decoder = nullptr;
    }
}

void BasicPlayerDecoderThread::run() {
    // 开始解码
    while (!stopFlag) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if (type == DecoderType::DECODER_TYPE_VIDEO) {
            if (playerCtr->GetVideoQueueSize() > 5) {
                continue;
            }
        } else if (type == DecoderType::DECODER_TYPE_AUDIO) {
            if (playerCtr->GetAudioQueueSize() > 5) {
                continue;
            }
        }

        BasicAVPacket *pkt = nullptr;
        int ret = packetQueue.Pop(&pkt);
        if (ret) {
            // 对列为空，取不到packet
            continue;
        }
        decoder->SendPacket(pkt);
        while (true) {
            BasicAVFrame *frame = new BasicAVFrame();
            ret = decoder->RecvFrame(frame);
            if (ret) {
                break;
            }
            //printf("Decoder Success\n");

            // 通过 playerCtr 的句柄，向其塞入 Frame 数据
            if (type == DecoderType::DECODER_TYPE_VIDEO) {
                playerCtr->PushFrameToVideoQueue(frame);
            } else if (type == DecoderType::DECODER_TYPE_AUDIO) {
                playerCtr->PushFrameToAudioQueue(frame);
            }
        }


    }
}


int BasicPlayerDecoderThread::Init(BasicAVStream *avStream) {
    return decoder->Init(avStream);
}

int BasicPlayerDecoderThread::PutPacket(BasicAVPacket *pkt) {
    return packetQueue.Push(pkt);
}

int BasicPlayerDecoderThread::GetPacketQueueSize() {
    return packetQueue.Size();
}