#ifndef MORPHEUSKEYS_H
#define MORPHEUSKEYS_H

#include <chrono>

namespace morpheus {
	enum class Keys : int {
		Up = 0,
		Left = 1,
		Down = 2,
		Right = 3,
		Jump = 4,
		RollLeft = 5,
		RollRight = 6
	};
	class KeyHandler {
	private:
		int keys [100];
	public:
		void resetToDefault();
		void setKey(Keys, int);
		int getKey(Keys);
	};
}

#endif // MORPHEUSKEYS_H