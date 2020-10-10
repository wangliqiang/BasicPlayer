extern "C" {
#include <libavformat/avformat.h>
}

class BasicAVStreamPrivate {
public:
	AVCodecParameters* codecpar = nullptr;
};