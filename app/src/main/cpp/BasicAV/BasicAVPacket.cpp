#include "BasicAV.h"
#include "BasicAVPacketPrivate.h"

BasicAVPacket::BasicAVPacket() {
	imp = new BasicAVPacketPrivate();
	imp->pkt = av_packet_alloc();
}
BasicAVPacket::~BasicAVPacket() {
	if (imp->pkt != nullptr) {
		av_packet_free(&imp->pkt);
		imp->pkt = nullptr;
	}

	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
}

int BasicAVPacket::GetIndex() {
	return imp->pkt->stream_index;
}