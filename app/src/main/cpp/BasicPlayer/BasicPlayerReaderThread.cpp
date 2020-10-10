#include "BasicPlayer.h"
#include "BasicAV/BasicAV.h"

BasicPlayerReaderThread::BasicPlayerReaderThread(std::string _path, double _seekTime, BasicPlayerController* _playerCtr) {
	path = _path;
	playerCtr = _playerCtr;
	seekTime = _seekTime;
}
BasicPlayerReaderThread::~BasicPlayerReaderThread() {

}

void BasicPlayerReaderThread::run() {
	BasicAVReader reader;
	int ret = reader.Open(path.c_str());
	if (ret) {
		return;
	}

	reader.Seek(seekTime);

	int videoStreamIndex = reader.GetVideoStreamIndex();
	int audioStreamIndex = reader.GetAudioStreamIndex();

	// 初始化解码器
	BasicPlayerDecoderThread* videoDecoderThread = new BasicPlayerDecoderThread(playerCtr, DecoderType::DECODER_TYPE_VIDEO);
	BasicPlayerDecoderThread* audioDecoderThread = new BasicPlayerDecoderThread(playerCtr, DecoderType::DECODER_TYPE_AUDIO);


	BasicAVStream videoStream;
	reader.GetStream(&videoStream, videoStreamIndex);
	videoDecoderThread->Init(&videoStream);

	BasicAVStream audioStream;
	reader.GetStream(&audioStream, audioStreamIndex);
	audioDecoderThread->Init(&audioStream);

	videoDecoderThread->Start();
	audioDecoderThread->Start();

	while (!stopFlag) {

		if (videoDecoderThread->GetPacketQueueSize() > 5 && audioDecoderThread->GetPacketQueueSize() > 5) {
			continue;
		}

		BasicAVPacket* pkt = new BasicAVPacket();
		int ret = reader.Read(pkt);
		if (ret) {
			delete pkt;
			pkt = nullptr;
			break;
		}

		if (pkt->GetIndex() == videoStreamIndex) {
			videoDecoderThread->PutPacket(pkt);
		}
		if (pkt->GetIndex() == audioStreamIndex) {
			audioDecoderThread->PutPacket(pkt);
		}


		// 将 Packet 放入缓存
		// printf("Read Packet Success\n");
	}

	// 释放资源
	videoDecoderThread->Stop();
	audioDecoderThread->Stop();

	reader.Close();

}