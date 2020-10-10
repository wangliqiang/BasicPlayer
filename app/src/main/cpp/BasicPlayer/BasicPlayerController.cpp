#include "BasicPlayer.h"

BasicPlayerController::BasicPlayerController(std::string _path, double _seekTime) {
    path = _path;
    seekTime = _seekTime;
}

BasicPlayerController::~BasicPlayerController() {

}

int BasicPlayerController::Play() {
    status = PlayerStatusCtr::VPLAYER_CTR_STATUS_PLAYING;
    return 0;
}

int BasicPlayerController::Pause() {
    status = PlayerStatusCtr::VPLAYER_CTR_STATUS_PAUSEING;
    return 0;
}

void BasicPlayerController::run() {

    BasicPlayerReaderThread readerThread(path, seekTime, this);
    readerThread.Start();

    // 获取线程启动时候的时间 startTime
    long long startTime = BasicAVTime::GetTime();

    BasicAVFrame *videoFrame = nullptr;
    BasicAVFrame *audioFrame = nullptr;

    long long sleepCountTime = 0;

    while (!stopFlag) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));


        long long sleepTimeStart = BasicAVTime::GetTime();
        while (status == VPLAYER_CTR_STATUS_PAUSEING) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        long long sleepTimeEnd = BasicAVTime::GetTime();

        long long sleepDTime = sleepTimeEnd - sleepTimeStart;

        sleepCountTime += sleepDTime;

        // 获取当前时间 nowTime
        long long nowTime = BasicAVTime::GetTime();

        // 获取当前时间和开始时间的差值 dTime
        long long dTime = nowTime - startTime;
        dTime = dTime - sleepCountTime;

        dTime = dTime + (long long) (seekTime * 1000);

        // 从视频缓存队列中，获取一帧视频 frame_pts
        if (videoFrame == nullptr) {
            // 尝试取一帧出来
            videoQueue.Pop(&videoFrame);
        }

        if (videoFrame != nullptr) {
            if (videoFrame->GetPts() < (long long) (seekTime * 1000)) {
                delete videoFrame;
                videoFrame = nullptr;
            }
        }

        if (videoFrame != nullptr) {
            // 如果frame_pts <= d_time
            if (videoFrame->GetPts() <= dTime) {
                // 这帧视频应该立即播放出来
                printf("Video Frame: %lld\n", videoFrame->GetPts());
                delete videoFrame;
                videoFrame = nullptr;
            } else {
                // 否则
                // 这帧视频还不到播放的时候，程序进行自旋，或者去处理音频
            }
        }

        // 从音频缓存队列中，获取一帧音频 farme_pts
        if (audioFrame == nullptr) {
            audioQueue.Pop(&audioFrame);
        }

        if (audioFrame != nullptr) {
            if (audioFrame->GetPts() < (long long) (seekTime * 1000)) {
                delete audioFrame;
                audioFrame = nullptr;
            }
        }
        if (audioFrame != nullptr) {
            // 如果frame_pts <= d_time
            if (audioFrame->GetPts() <= dTime) {
                // 这帧音频应该立即播放出来
                delete audioFrame;
                audioFrame = nullptr;
            } else {
                // 否则
                // 这帧音频还不到播放的时候，程序进行自旋，或者去处理视频
            }
        }
    }
    readerThread.Stop();
}

int BasicPlayerController::GetVideoQueueSize() {

    return videoQueue.Size();
}

int BasicPlayerController::GetAudioQueueSize() {

    return audioQueue.Size();
}

int BasicPlayerController::PushFrameToVideoQueue(BasicAVFrame *frame) {
    //printf("Vudio Queue Size: %d\n", videoQueue.Size());
    return videoQueue.Push(frame);
}

int BasicPlayerController::PushFrameToAudioQueue(BasicAVFrame *frame) {

    return audioQueue.Push(frame);
}