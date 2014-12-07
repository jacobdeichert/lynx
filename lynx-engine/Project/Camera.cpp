#include "Camera.h"
using namespace lynx;


Camera::Camera() {}



Camera::Camera(float aspectRatio) {
	fov = 70.0f;
	near = 0.1f;
	far = 1000.0f;
	this->aspectRatio = aspectRatio;

	transform->position = glm::vec3(0, 0, -10.0f); // eye
	//direction = glm::vec3(0, 0, -1); // center
	//up = glm::vec3(0, 1, 0);
}


Camera::~Camera() {}


void Camera::update() {
	//model = glm::mat4();

	//// Translate to the position (mat4 is the identity matrix).
	//model = glm::translate(model, position);

	//// Rotate each axis.
	//model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
	//model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
	//model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));


	//view = glm::inverse(model);
	// If the pitch and yaw angles are in degrees,
	// they need to be converted to radians.
	float cosPitch = cos(glm::radians(transform->rotation.x));
	float sinPitch = sin(glm::radians(transform->rotation.x));
	float cosYaw = cos(glm::radians(transform->rotation.y));
	float sinYaw = sin(glm::radians(transform->rotation.y));

	glm::vec3 xaxis = { cosYaw, 0, -sinYaw };
	glm::vec3 yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	glm::vec3 zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

	// Create a 4x4 view matrix from the right, up, forward and eye position vectors
	view = {
		-xaxis.x, yaxis.x, -zaxis.x, 0,
		-xaxis.y, yaxis.y, -zaxis.y, 0,
		-xaxis.z, yaxis.z, -zaxis.z, 0,
		glm::dot(xaxis, transform->position), -glm::dot(yaxis, transform->position), glm::dot(zaxis, transform->position), 1
	};




	//view = glm::lookAt(position, position + direction, up);
	transform->model = glm::inverse(view);
	//model = glm::mat4();
	/*model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
	model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));*/
	
	//view = glm::inverse(model);

	

	// FPS camera: http://3dgep.com/understanding-the-view-matrix/

	projection = glm::perspective(
		fov,			// The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		aspectRatio,	// Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		near,			// Near clipping plane. Keep as big as possible, or you'll get precision issues.
		far);			// Far clipping plane. Keep as little as possible.
}

//
//glm::vec3 Camera::forward() {
//	return -glm::normalize(glm::vec3(view[0][2], view[1][2], view[2][2]));
//}
//
//
//
//glm::vec3 Camera::left() {
//	return -glm::normalize(glm::vec3(view[0][0], view[1][0], view[2][0]));
//}
