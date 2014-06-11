#include "MorpheusModel.h"
#include "MorpheusError.h"
#include <iostream>

namespace morpheus {
	Model::Model(GLfloat* verts, int vertlen, int vertOffset, int normOffset, int UVOffset, int stride, GLuint* indices, int indlen, int size){
		drawSize = size;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertlen, verts, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)vertOffset);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)normOffset);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)UVOffset);
		glEnableVertexAttribArray(2);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indlen, indices, GL_STATIC_DRAW);

		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

		morpheus::handleError(morpheus::Error::GL_CREATE_VBO, true);
	}
	Model::~Model(){
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &VBO);

		glBindVertexArray(0);
		glDeleteVertexArrays(1, &VAO);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &IBO);

		morpheus::handleError(morpheus::Error::GL_DESTROY_VBO, true);
	}
	void Model::draw(){
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, drawSize, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}
}