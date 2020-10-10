#pragma once

#include <queue>
#include <mutex>


/*
 * 泛型
 */
template<typename T>

class BasicQueue {
public:
	BasicQueue() {

	}
	~BasicQueue() {
		std::lock_guard<std::mutex> lock(mut);
		while (Size() > 0) {
			// T * t = queue.front();
			queue.pop();
		}
	}

	int Push(T* t) {
		std::lock_guard<std::mutex> lock(mut);
		queue.push(t);
		return 0;
	}
	int Pop(T** t) {
		std::lock_guard<std::mutex> lock(mut);
		int size = Size();
		if (size > 0) {
			*t = queue.front();
			queue.pop();
			return 0;
		}
		return -1;
	}

	int Size() {
		return queue.size();
	}

private:
	std::queue<T *> queue;
	std::mutex mut;
};