#ifndef MORPHEUSTEXTURE_H
#define MORPHEUSTEXTURE_H

#include <GL/glew.h>

namespace morpheus {
	class Texture {
	private:
		GLuint id;
		int width, height;
	public:
		Texture(unsigned char* data, int w, int h);
		~Texture();
		void bind();
	};
}

#endif // MORPHEUSTEXTURE_H