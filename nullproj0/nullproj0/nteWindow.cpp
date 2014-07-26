#include "nteWindow.h"
#include "nteError.h"
#include <GL/glew.h>
#include <iostream>
#include <string>

namespace nte {
	int indexOf(std::string str1, std::string f){
		std::string::size_type loc = str1.find(f, 0);
		if (loc != std::string::npos) {
			return loc;
		} else {
			return -1;
		}
	}
	bool Window::create(std::string title, int w, int h) {
		SCREEN_WIDTH = w;
		SCREEN_HEIGHT = h;
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		window = SDL_CreateWindow(&title[0], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
		if (window == NULL)
		{
			std::cout << "Window: \"" << title << "\" creation failed. SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}
		context = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, context);
		nte::handleError(nte::Error::CREATE_WINDOW, true);
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			nte::handleError(nte::Error::GL_GLEW_INIT, false);
		}
		nte::handleError(nte::Error::GL_GLEW_INIT, true);
		title = title + " OpenGL V" + (char*)glGetString(GL_VERSION);
		SDL_SetWindowTitle(window, &title[0]);
		surface = SDL_GetWindowSurface(window);
		exists = true;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		return true;
	}
	bool Window::show(){
		SDL_ShowWindow(window);
		return true;
	}
	void Window::setTitle(std::string title, bool appendOpenGLV, int fps, double et, double ut, double rt, double tt){
		if (appendOpenGLV){
			int maj = -1;
			int min = -1;
			glGetIntegerv(GL_MAJOR_VERSION, &maj);
			glGetIntegerv(GL_MINOR_VERSION, &min);
			title = title + " OpenGL V" + std::to_string(maj) + "." + std::to_string(min);
		}
		title = title + " FPS: " + std::to_string(fps) + " at " + std::to_string(tt).substr(0, indexOf(std::to_string(tt), ".") + 2) + "ms/frame" + ", Events " + std::to_string(et).substr(0, indexOf(std::to_string(et), ".") + 2) + "ms, Update " + std::to_string(ut).substr(0, indexOf(std::to_string(ut), ".") + 2) + "ms, Render " + std::to_string(rt).substr(0, indexOf(std::to_string(rt), ".") + 2) + "ms";
		SDL_SetWindowTitle(window, &title[0]);
	}
	bool Window::beginDraw() {
		SDL_GL_MakeCurrent(window, context);
		return true;
	}
	bool Window::endDraw() {
		SDL_GL_SwapWindow(window);
		return true;
	}
	bool Window::destroy() {
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
		exists = false;
		return true;
	}
}
