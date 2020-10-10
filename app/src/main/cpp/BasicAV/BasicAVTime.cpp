#include "BasicAV.h"

#include <chrono>

long long BasicAVTime::GetTime() {
	std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds> tp =
		std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());


	auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());

	return (long long)tmp.count();
}