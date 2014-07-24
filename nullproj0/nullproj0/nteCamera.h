#ifndef NTECAMERA_H
#define NTECAMERA_H

#include "nteShader.h"
#include <glm/glm.hpp>

namespace nte {
	class Camera {
	private:
		glm::mat4x4 projection;
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		void createOrthographicProjectionMatrix(float width, float height);
		void createPerspectiveProjectionMatrix(float width, float height, float near, float far, float fov);
		void bind(Shader* s);
		glm::mat4x4 getProjection();
		glm::mat4x4 getView();
	};
}

#endif // NTECAMERA_H