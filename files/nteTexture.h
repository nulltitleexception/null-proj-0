#ifndef NTETEXTURE_H
#define NTETEXTURE_H

#include <GL/glew.h>

namespace nte {
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

#endif // NTETEXTURE_H