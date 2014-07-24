#include "nteTexture.h"

namespace nte {
	Texture::Texture(unsigned char* data, int w, int h){
		width = w;
		height = h;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	Texture::~Texture(){
		if (id != 0)
		{
			glDeleteTextures(1, &id);
			id = 0;
		}
		width = 0;
		height = 0;

	}
	void Texture::bind(){
		glBindTexture(GL_TEXTURE_2D, id);
	}
}