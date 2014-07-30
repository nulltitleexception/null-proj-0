#include "nteKeys.h"

namespace nte {
	KeyHandler::KeyHandler(){
		for (int i = 0; i < KEY_NUMBER; i++){
			isDownPrev[i] = false;
			isDown[i] = false;
		}
		resetToDefault();
	}
	KeyHandler::~KeyHandler(){

	}
	int KeyHandler::getKeysAsInt(Keys k){
		return static_cast<int>(k);
	}
	void KeyHandler::resetToDefault(){
		keys[getKeysAsInt(Keys::Up)] = 'w';
		keys[getKeysAsInt(Keys::Left)] = 'a';
		keys[getKeysAsInt(Keys::Down)] = 's';
		keys[getKeysAsInt(Keys::Right)] = 'd';
		keys[getKeysAsInt(Keys::Jump)] = ' ';
		keys[getKeysAsInt(Keys::RollLeft)] = 'q';
		keys[getKeysAsInt(Keys::RollRight)] = 'e';
	}
	void KeyHandler::setKey(Keys k, int sdlKeyCode){
		keys[getKeysAsInt(k)] = sdlKeyCode;
	}
	int KeyHandler::getKey(Keys k){
		return keys[getKeysAsInt(k)];
	}
	void KeyHandler::swapKeys(int k1, int k2){
		int k1Slot = -1;
		int k2Slot = -1;
		for (int i = 0; i < KEY_NUMBER; i++){
			if (keys[i] == k1){
				k1Slot = i;
			}
			if (keys[i] == k2){
				k2Slot = i;
			}
		}
		if (k1Slot >= 0){
			keys[k1Slot] = k2;
		}
		if (k2Slot >= 0){
			keys[k2Slot] = k1;
		}
	}
	void KeyHandler::handleKeyPress(int k){
		for (int i = 0; i < KEY_NUMBER; i++){
			if (keys[i] == k){
				isDown[i] = true;
			}
		}
	}
	bool KeyHandler::isKeyDown(Keys k){
		return isDown[getKeysAsInt(k)];
	}
	bool KeyHandler::wasKeyPressed(Keys k){
		return isDown[getKeysAsInt(k)] && !isDownPrev[getKeysAsInt(k)];
	}
	void KeyHandler::update(){
		for (int i = 0; i < KEY_NUMBER; i++){
			isDownPrev[i] = isDown[i];
			isDown[i] = false;
		}
	}
}