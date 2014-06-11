#ifndef MORPHEUSTRANSFORM_H
#define MORPHEUSTRANSFORM_H

#include <glm/glm.hpp>

namespace morpheus {
	class Transform {
	public:
		Transform();
		glm::vec3 position = glm::vec3(0);
		glm::vec3 rotation = glm::vec3(0);
		glm::vec3 scale = glm::vec3(1, 1, 1);
		glm::mat4x4 getAsMatrix();
	};
}

#endif // MORPHEUSTRANSFORM_H