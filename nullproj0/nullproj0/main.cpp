//null-proj-0
//libraries used: opengl, glew, glm, SDL2, lodepng
#include "nteError.h"
#include "nteWindow.h"
#include "nteCamera.h"
#include "nteVoxelMap.h"
#include "nteGameObject.h"
#include "nteTransform.h"
#include "nteKeys.h"
#include "nteTime.h"
#include "nteShader.h"
#include "nteResourceManager.h"
#include "nteModel.h"
#include "nteNoise.h"
#include <GL/glew.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <mutex>
#include <thread>
#include <chrono>
#include <math.h>
#include <iostream>
#include <random>
#include <exception>
//#include <vld.h>
#define main main

int handleQuit(std::thread* thisThread, double elapsedTime) {
	std::cout << "The program has quit.  " << (elapsedTime / 1000) << " seconds elapsed." << std::endl;
	return 0;
}

void handleKeyChange(nte::KeyHandler* keys) {
	std::cout << "Modify which key?" << std::endl;
	char k1 = 0;
	std::cin >> k1;

	std::cout << "Swap with what?" << std::endl;
	char k2 = 0;
	std::cin >> k2;

	keys->swapKeys(k1, k2);
	std::cout << "Keys Swapped" << std::endl;
}

int main(int argc, char** argv) {
	try {
		nte::Timer programTime;
		programTime.start();

		//this is here as an example prng, in case I forget.  I was pretty surprised to find a mersenne twister implementation in the standard library.
		/*std::mt19937_64 rng;
		//rng.seed(std::chrono::duration <double, std::milli>(std::chrono::steady_clock::now().time_since_epoch()).count());
		rng.seed(); //not random, whereas above uses time to introduce inital entropy requirement.
		for (int i = 0; i < 10; ++i){
		std::cout << rng() << std::endl;
		}*/

		nte::Window window;
		nte::KeyHandler* keys;

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cout << "SDL initialization failed. SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		SDL_SetRelativeMouseMode(SDL_TRUE);

		keys = new nte::KeyHandler();

		std::string title = "nte";
		window.create(title, 1600, 900);

		nte::ResourceManager* resources = new nte::ResourceManager("manifest.mf");
		title += " " + resources->getVersion();

		//converts a .obj file into a .vnf file
		//removeme
		//resources->convertObjModel("monkey_smooth");
		//int d = 0;
		//std::cin >> d; 
		//return 0;
		//endremoveme 

		/*nte::GameObject* go;
		go = new nte::GameObject();
		go->addModelByReference(resources->getModel("cube_sharp"));
		go->addUniqueTransform(new nte::Transform());
		go->addTextureByReference(resources->getTexture("sphere"));*/
		//go->addUniqueTexture(new nte::Texture(&noiseData[0], 500, 500));

		nte::VoxelMap* vox;
		vox = new nte::VoxelMap(300, 300, 300);
		vox->generateTerrain();
		vox->generateHeightmap();
		vox->generateModel();

		nte::Camera camera;
		camera.createPerspectiveProjectionMatrix(1600, 900, 0.01f, 100000.0f, glm::radians(90.0f));
		//camera.position.z = 100;

		bool paused = false;

		window.show();

		bool shouldExit = false;

		SDL_Event event;
		int frameCount = 0;
		int fps = 0;
		nte::Timer fpsTime;

		nte::Timer frameTime;
		double eventTime = 0;
		double updateTime = 0;
		double renderTime = 0;

		nte::Timer updateDeltaTimer;

		std::cout << "Entering game loop..." << std::endl;
		fpsTime.start();
		updateDeltaTimer.start();
		while (!shouldExit) {
			frameTime.start();
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					shouldExit = true;
					break;
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
					case SDL_WINDOWEVENT_CLOSE:
						shouldExit = true;
						break;
					}
					break;
				case SDL_MOUSEMOTION:
					camera.rotation.x -= event.motion.yrel / 40.0f;
					camera.rotation.y -= event.motion.xrel / 40.0f;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_F2){
						handleKeyChange(keys);
					} else
					if (event.key.keysym.sym == SDLK_F6){
						static bool isWireFrame = false;
						isWireFrame = !isWireFrame;
						if (isWireFrame){
							glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
						} else {
							glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
						}
					} else{
						keys->handleKeyPress(event.key.keysym.sym, true);
					}
					break;
				case SDL_KEYUP:
					keys->handleKeyPress(event.key.keysym.sym, false);
					break;
				}
			}
			eventTime = frameTime.getMillis();
			if (!shouldExit && !paused){
				double delta = updateDeltaTimer.getMillis();
				updateDeltaTimer.start();
				double speed = 0.002;
				int forward = 0;
				int left = 0;
				int angle = -1;
				if (keys->isKeyDown(nte::Keys::Sprint)){
					speed *= 20;
				}
				if (keys->isKeyDown(nte::Keys::Jump)){
					speed *= 100;
				}
				if (keys->isKeyDown(nte::Keys::RollLeft)){
					camera.position.y -= speed;
				}
				if (keys->isKeyDown(nte::Keys::RollRight)){
					camera.position.y += speed;
				}
				if (keys->isKeyDown(nte::Keys::Up)){
					forward++;
				}
				if (keys->isKeyDown(nte::Keys::Down)){
					forward--;
				}
				if (keys->isKeyDown(nte::Keys::Left)){
					left++;
				}
				if (keys->isKeyDown(nte::Keys::Right)){
					left--;
				}
				if (forward == 0 && left == 0){
				} else if (forward == 1 && left == 0){
					angle = 0;
				} else if (forward == 1 && left == -1){
					angle = 1;
				} else if (forward == 0 && left == -1){
					angle = 2;
				} else if (forward == -1 && left == -1){
					angle = 3;
				} else if (forward == -1 && left == 0){
					angle = 4;
				} else if (forward == -1 && left == 1){
					angle = 5;
				} else if (forward == 0 && left == 1){
					angle = 6;
				} else if (forward == 1 && left == 1){
					angle = 7;
				}
				if (angle != -1){
					camera.position.x += speed * delta * sin((angle * (M_PI / 4)) - glm::radians(camera.rotation.y));
					camera.position.z -= speed * delta * cos((angle * (M_PI / 4)) - glm::radians(camera.rotation.y));
				}
				//camera.position.y = vox->getHeightAt(camera.position.x, camera.position.z) + 0.02;
				keys->update();
			}
			updateTime = frameTime.getMillis() - eventTime;
			if (!shouldExit){
				window.beginDraw();
				glClearColor(0, 0, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				//std::string shaderToUse = "texture_test";
				std::string shaderToUse = "voxel_map";
				resources->getShader(shaderToUse)->bind();
				camera.bind(resources->getShader(shaderToUse));
				//go->draw(resources->getShader(shaderToUse));
				int modMatPos = glGetUniformLocation(resources->getShader(shaderToUse)->getID(), "modelMatrix");
				nte::Transform* temp = new nte::Transform();
				glUniformMatrix4fv(modMatPos, 1, GL_FALSE, &(temp->getAsMatrix()[0][0]));
				vox->draw();
				window.endDraw();
				nte::handleError(nte::Error::GL_DRAW, true);
			}
			renderTime = frameTime.getMillis() - (updateTime + eventTime);
			frameCount++;
			if (fpsTime.getMillis() >= 1000){
				fps = frameCount;
				frameCount = 0;
				fpsTime.start();
			}
			window.setTitle(title, true, fps, eventTime, updateTime, renderTime, frameTime.getMillis());
		}
		//delete go;
		delete vox;
		delete resources;
		delete keys;
		window.destroy();
		SDL_Quit();
		std::thread quitHandler = std::thread(handleQuit, &quitHandler, programTime.getMillis());
		quitHandler.join();
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	} catch (std::exception& e){
		nte::handleError(nte::Error::UNCAUGHT, false);
		std::cout << e.what() << std::endl;
	} catch (...) {
		nte::handleError(nte::Error::UNCAUGHT, false);
	}
	int keytoexit = 0;
	std::cin >> keytoexit;
	return 0;
}