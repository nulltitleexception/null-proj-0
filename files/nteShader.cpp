#include "nteShader.h"
#include "nteError.h"
#include <iostream>
#include <string>
#include <fstream>

namespace nte {
	Shader::Shader(const GLchar* VertexShader, const GLchar* FragmentShader)
	{
		VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VertexShaderId, 1, &VertexShader, 0);
		glCompileShader(VertexShaderId);

		FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragmentShaderId, 1, &FragmentShader, 0);
		glCompileShader(FragmentShaderId);

		ProgramId = glCreateProgram();
		glAttachShader(ProgramId, VertexShaderId);
		glAttachShader(ProgramId, FragmentShaderId);
		glLinkProgram(ProgramId);
		glUseProgram(ProgramId);

		nte::handleError(nte::Error::GL_CREATE_SHADER, true);
	}
	Shader::~Shader()
	{
		glUseProgram(0);

		glDetachShader(ProgramId, VertexShaderId);
		glDetachShader(ProgramId, FragmentShaderId);

		glDeleteShader(FragmentShaderId);
		glDeleteShader(VertexShaderId);

		glDeleteProgram(ProgramId);

		nte::handleError(nte::Error::GL_DESTROY_SHADER, true);
	}
	void Shader::bind(){
		glUseProgram(ProgramId);
	}
}