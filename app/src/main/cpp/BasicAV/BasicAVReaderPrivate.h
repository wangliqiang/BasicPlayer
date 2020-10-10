extern "C" {
#include <libavformat/avformat.h>
}

class BasicAVReaderPrivate {
public:
	AVFormatContext* formatCtx = nullptr;
};