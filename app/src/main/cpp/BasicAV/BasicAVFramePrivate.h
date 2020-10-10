extern "C" {
#include <libavformat/avformat.h>
}

class BasicAVFramePrivate {
public:
	AVFrame* frame = nullptr;
	double ptsSec = 0.0;
};