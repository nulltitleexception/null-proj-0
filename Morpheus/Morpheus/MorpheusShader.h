#ifndef MORPHEUSSHADER_H
#define MORPHEUSSHADER_H

#include <string>
#include <GL/glew.h>

namespace morpheus {
	class Shader {
	private:
		GLuint VertexShaderId, FragmentShaderId, ProgramId;
	public:
		Shader(const GLchar*, const GLchar*);
		~Shader();
		void bind();
		GLuint getID(){ return ProgramId; }
	};
}

#endif // MORPHEUSSHADER_H