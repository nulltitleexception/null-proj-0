#ifndef NTETIME_H
#define NTETIME_H

#include <chrono>

namespace nte {
	class Timer {
	private:
		std::chrono::steady_clock::time_point startTime;
	public:
		void start();
		double getMillis();
	};
}

#endif // NTETIME_H