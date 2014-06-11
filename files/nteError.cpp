#include "nteError.h"
#include <GL/glew.h>
#include <vector>
#include <iostream>

namespace nte {
	void handleError(Error e, bool gle){
		if (gle){
			GLenum ErrorCheckValue = glGetError();
			if (ErrorCheckValue != GL_NO_ERROR) {
				std::cout << "GL Error " << static_cast<int>(e) << ": " << gluErrorString(ErrorCheckValue) << std::endl;
			}
		}
		else {
			std::cout << "Error " << static_cast<int>(e) << std::endl;
		}
	}
}