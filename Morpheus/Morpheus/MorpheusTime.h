#ifndef MORPHEUSTIME_H
#define MORPHEUSTIME_H

#include <chrono>

namespace morpheus {
	class Timer {
	private:
		std::chrono::steady_clock::time_point startTime;
	public:
		void start();
		double getMillis();
	};
}

#endif // MORPHEUSTIME_H