extern "C" {
#include <libavcodec/avcodec.h>
}

class BasicAVDecoderPrivate {
public:
	AVCodecContext* codecCtx = nullptr;
};