#include "MorpheusTransform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace morpheus {
	Transform::Transform(){
		position = glm::vec3(0, 0, 0);
		rotation = glm::vec3(0, 0, 0);
		scale = glm::vec3(1, 1, 1);
	}
	glm::mat4x4 Transform::getAsMatrix(){
		return glm::translate(position) * glm::rotate(rotation.y, glm::vec3(0, 1, 0)) * glm::rotate(rotation.x, glm::vec3(1, 0, 0)) * glm::rotate(rotation.z, glm::vec3(0, 0, 1));
	}
}