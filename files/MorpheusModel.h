#ifndef MORPHEUSMODEL_H
#define MORPHEUSMODEL_H

#include <GL/glew.h>

namespace morpheus {
	class Model {
	private:
		GLuint VAO, VBO, IBO;//vertex array, vertex buffer, normal buffer, texture buffer, and index buffer objects
		int drawSize;
	public:
		Model(GLfloat* verts, int vertlen, int vertOffset, int normOffset, int UVOffset, int stride, GLuint* indices, int indlen, int size);
		~Model();
		void draw();
	};
}

#endif // MORPHEUSMODEL