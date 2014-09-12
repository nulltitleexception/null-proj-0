#include "nteWorld.h"
nte::World::World(){
	goMax = -1;
}
nte::World::~World(){
}
int nte::World::addGameObject(GameObject* go){
	for (int i = 0; i < goLen; i++){
		if (gameObjects[i] == nullptr){
			gameObjects[i] = go;
			if (i > goMax){
				goMax = i;
			}
			return i;
		}
	}
	return -1;
}
void nte::World::removeGameObject(int go){
	if (go >= 0 && go <= goMax){
		delete gameObjects[go];
		if (go == goMax){
			for (int i = goMax - 1; i >= 0; i--){
				if (gameObjects[i] != nullptr){
					goMax = i;
				}
			}
			if (goMax == go){
				goMax = -1;
			}
		}
	}
}
nte::GameObject* nte::World::getGameObject(int go){
	if (go >= 0 && go <= goMax){
		return gameObjects[go];
	}
	return nullptr;
}
void nte::World::draw(Shader* s){
	for (int i = 0; i < goMax)
}