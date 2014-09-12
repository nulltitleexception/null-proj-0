#ifndef NTEWORLD_H
#define NTEWORLD_H

#include "nteGameObject.h"

namespace nte {
	class World {
	private:
		int goMax; // current highest id of any game object (varies as objects are added and removed), must be >= ( (# of GO) - 1 )
		int goLen = 100;
		GameObject* gameObjects[100];
	public:
		World();
		~World();
		int addGameObject(GameObject*);
		void removeGameObject(int);
		GameObject* getGameObject(int);
		void draw(Shader* s);
	};
}

#endif // NTEWORLD_H