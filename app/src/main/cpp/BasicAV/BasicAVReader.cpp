#include "BasicAV.h"
#include "BasicAVReaderPrivate.h"
#include "BasicAVPacketPrivate.h"
#include "BasicAVDecoderPrivate.h"
#include "BasicAVStreamPrivate.h"


BasicAVReader::BasicAVReader() {
	imp = new BasicAVReaderPrivate();
	imp->formatCtx = avformat_alloc_context();
}

BasicAVReader::~BasicAVReader() {
	if (imp->formatCtx != nullptr) {
		avformat_free_context(imp->formatCtx);
		imp->formatCtx = nullptr;
	}
	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
}

int BasicAVReader::Open(char const* path) {
	if (imp->formatCtx == nullptr) {
		return -1;
	}
	int ret = avformat_open_input(&imp->formatCtx, path, nullptr, nullptr);
	
	if (!ret) {
		avformat_find_stream_info(imp->formatCtx,nullptr);
	}

	return ret;
}

int BasicAVReader::GetStreamCount() {
	return imp->formatCtx->nb_streams;
}

int BasicAVReader::GetStream(BasicAVStream* avStream, int streamId) {
	AVStream* ffmpegStream = imp->formatCtx->streams[streamId];

	avStream->timebaseNum = ffmpegStream->time_base.num;
	avStream->timebaseDen = ffmpegStream->time_base.den;
	avStream->streamIndex = ffmpegStream->index;

	avcodec_parameters_copy(avStream->imp->codecpar, ffmpegStream->codecpar);

	return 0;
}

int BasicAVReader::GetVideoStreamIndex()
{
	return av_find_best_stream(imp->formatCtx, AVMediaType::AVMEDIA_TYPE_VIDEO, -1, -1, NULL, NULL);
}

int BasicAVReader::GetAudioStreamIndex()
{
	return av_find_best_stream(imp->formatCtx, AVMediaType::AVMEDIA_TYPE_AUDIO, -1, -1, NULL, NULL);
}


int BasicAVReader::Close() {
	if (imp->formatCtx == nullptr) {
		return -1;
	}
	avformat_close_input(&imp->formatCtx);
	return 0;

}

int BasicAVReader::Read(BasicAVPacket* packet) {
	if (imp->formatCtx == nullptr) {
		return -1;
	}
	int ret = av_read_frame(imp->formatCtx, packet->imp->pkt);
	return ret;
}

int BasicAVReader::Seek(double time) {
	if (imp->formatCtx == nullptr) {
		return -1;
	}

	int64_t timestamp = (int64_t)(time * AV_TIME_BASE);
	av_seek_frame(imp->formatCtx, -1, timestamp, AVSEEK_FLAG_BACKWARD);

	return 0;
}