#ifndef NTESHADER_H
#define NTESHADER_H

#include <string>
#include <GL/glew.h>

namespace nte {
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

#endif // NTESHADER_H