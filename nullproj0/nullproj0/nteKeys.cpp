#include "nteKeys.h"

namespace nte {
		void KeyHandler::resetToDefault(){
			keys[static_cast<int>(Keys::Up)] = 'w';
			keys[static_cast<int>(Keys::Left)] = 'a';
			keys[static_cast<int>(Keys::Down)] = 's';
			keys[static_cast<int>(Keys::Right)] = 'd';
			keys[static_cast<int>(Keys::Jump)] = ' ';
			keys[static_cast<int>(Keys::RollLeft)] = 'q';
			keys[static_cast<int>(Keys::RollRight)] = 'e';
		}
		void KeyHandler::setKey(Keys k, int sdlKeyCode){
			keys[static_cast<int>(k)] = sdlKeyCode;
		}
		int KeyHandler::getKey(Keys k){
			return keys[static_cast<int>(k)];
		}
	
}