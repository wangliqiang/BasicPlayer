#include "BasicThread.h"
#include <thread>

int BasicThread::Start() {
	if (t == nullptr) {
		stopFlag = 0;
		t = new std::thread(&BasicThread::run, this);
	}
	return 0;
}

int BasicThread::Stop() {
	if (t != nullptr) {
		stopFlag = 1;
		t->join();
		delete t;
		t = nullptr;
	}
	return 0;
}