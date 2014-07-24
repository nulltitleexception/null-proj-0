#ifndef NTEWINDOW_H
#define NTEWINDOW_H

#include "SDL.h"
#include <string>
#include <mutex>

namespace nte {
	class Window {
	public:
		bool exists = false;
		int SCREEN_WIDTH = 640;
		int SCREEN_HEIGHT = 480;
		SDL_Window* window = NULL;
		SDL_Surface* surface = NULL;
		SDL_GLContext context = NULL;
		bool create(std::string, int, int);
		bool show();
		void setTitle(std::string title, bool appendOpenGLV, int fps, double et, double ut, double rt, double tt);
		bool beginDraw();
		bool endDraw();
		bool destroy();
	};
}
#endif // NTEWINDOW_H
