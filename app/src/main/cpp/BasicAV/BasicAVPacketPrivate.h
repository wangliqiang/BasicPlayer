extern "C" {
#include <libavformat/avformat.h>
}

class BasicAVPacketPrivate {
public:
	AVPacket* pkt = nullptr;
};