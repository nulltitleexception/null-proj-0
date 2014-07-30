#ifndef NTEKEYS_H
#define NTEKEYS_H

#include <chrono>

#define KEY_NUMBER 100

namespace nte {
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
		int keys[KEY_NUMBER];
		bool isDown[KEY_NUMBER];
		bool isDownPrev[KEY_NUMBER];
		int getKeysAsInt(Keys);
	public:
		KeyHandler();
		~KeyHandler();
		void resetToDefault();
		void setKey(Keys, int);
		int getKey(Keys);
		void swapKeys(int, int);
		void handleKeyPress(int);
		bool isKeyDown(Keys);
		bool wasKeyPressed(Keys);
		void update();
	};
}

#endif // NTEKEYS_H