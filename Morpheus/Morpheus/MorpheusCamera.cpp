#include "MorpheusCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace morpheus {
	void Camera::createOrthographicProjectionMatrix(float width, float height){
		projection = glm::ortho(0.0f,width,0.0f,height);
	}
	void Camera::createPerspectiveProjectionMatrix(float width, float height, float near, float far, float fov){
		projection = glm::perspective(fov, width / height, near, far);
	}
	void Camera::bind(Shader* s){
		int projMatPos = glGetUniformLocation(s->getID(), "projectionMatrix");
		glUniformMatrix4fv(projMatPos, 1, GL_FALSE, &(projection[0][0]));
		int viewMatPos = glGetUniformLocation(s->getID(), "viewMatrix");
		glUniformMatrix4fv(viewMatPos, 1, GL_FALSE, &(getView()[0][0]));
	}
	glm::mat4x4 Camera::getProjection(){
		return projection;
	}
	glm::mat4x4 Camera::getView(){
		return glm::translate(position * -1.0f) * glm::rotate(-rotation.y, glm::vec3(0, 1, 0)) * glm::rotate(-rotation.x, glm::vec3(1, 0, 0)) * glm::rotate(-rotation.z, glm::vec3(0, 0, 1));
	}
}