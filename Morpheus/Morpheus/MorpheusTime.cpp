#include "MorpheusTime.h"

namespace morpheus {
	void Timer::start(){
		startTime = std::chrono::steady_clock::now();
	}
	double Timer::getMillis(){
		auto endTime = std::chrono::steady_clock::now();
		auto elapsedTime = endTime - startTime;
		return std::chrono::duration <double, std::milli>(elapsedTime).count();
	}
}