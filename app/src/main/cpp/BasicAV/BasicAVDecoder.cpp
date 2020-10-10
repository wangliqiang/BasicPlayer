#include "BasicAV.h"
#include "BasicAVDecoderPrivate.h";
#include "BasicAVStreamPrivate.h";
#include "BasicAVPacketPrivate.h";
#include "BasicAVFramePrivate.h";

BasicAVDecoder::BasicAVDecoder() {
	imp = new BasicAVDecoderPrivate();
	imp->codecCtx = avcodec_alloc_context3(nullptr);
}
BasicAVDecoder::~BasicAVDecoder() {
	if (imp->codecCtx != nullptr) {
		avcodec_free_context(&imp->codecCtx);
		imp->codecCtx = nullptr;
	}

	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
}

int BasicAVDecoder::Init(BasicAVStream* stream) {

	timebaseNum = stream->timebaseNum;
	timebaseDen = stream->timebaseDen;
	
	avcodec_parameters_to_context(imp->codecCtx,stream->imp->codecpar);
	AVCodec* avCodec = avcodec_find_decoder(imp->codecCtx->codec_id);

	int ret = avcodec_open2(imp->codecCtx, avCodec,nullptr);
	if (ret) {
		printf("avodec_open2 fail ret: %d\n", ret);
		return -1;
	}
	return 0;
}

int BasicAVDecoder::SendPacket(BasicAVPacket* packet) {
	int ret = 0;
	if (packet == nullptr) {
		ret = avcodec_send_packet(imp->codecCtx, nullptr);
	}
	else {
		ret = avcodec_send_packet(imp->codecCtx, packet->imp->pkt);
	}
	return ret;
}
int BasicAVDecoder::RecvFrame(BasicAVFrame* frame) {

	int ret = avcodec_receive_frame(imp->codecCtx, frame->imp->frame);
	if (!ret) {
		// 将秒级时间戳计算并且赋值
		frame->imp->ptsSec = frame->imp->frame->pts * 1.0 * timebaseNum / timebaseDen;
	}
	return ret;
}

int BasicAVDecoder::Close() {
	return avcodec_close(imp->codecCtx);
}