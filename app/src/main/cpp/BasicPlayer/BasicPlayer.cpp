#include "BasicPlayer.h"

BasicPlayer::BasicPlayer(std::string _path) {
    path = _path;
}

BasicPlayer::~BasicPlayer() {

}

int BasicPlayer::Open(double time) {
    if (playerCtr == nullptr) {
        playerCtr = new BasicPlayerController(path, time);
        playerCtr->Start();
        return 0;
    }

    return -1;
}

int BasicPlayer::Stop() {
    if (playerCtr != nullptr) {
        playerCtr->Stop();
        delete playerCtr;
        playerCtr = nullptr;
    }
    return 0;
}

int BasicPlayer::Play() {
    if (playerCtr != nullptr) {
        playerCtr->Play();
    }
    return 0;
}

int BasicPlayer::Pause() {
    if (playerCtr != nullptr) {
        playerCtr->Pause();
    }
    return 0;
}

int BasicPlayer::Seek(double time) {
    Stop();
    Open(time);
    return 0;
}