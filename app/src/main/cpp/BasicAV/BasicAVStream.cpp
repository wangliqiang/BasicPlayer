#include "BasicAV.h"
#include "BasicAVStreamPrivate.h";

BasicAVStream::BasicAVStream() {
	imp = new BasicAVStreamPrivate();
	imp->codecpar = avcodec_parameters_alloc();
}

BasicAVStream::~BasicAVStream() {
	if (imp->codecpar != nullptr) {
		(&imp->codecpar);
		avcodec_parameters_free(&imp->codecpar);
		imp->codecpar = nullptr;
	}
	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
}