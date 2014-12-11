#include "Camera.h"
#include "GameObject.h"
#include "ShaderManager.h"
using namespace lynx;



Camera::Camera(GameObject *gameObject, float aspectRatio, glm::vec4 clearColor) : Component(gameObject) {
	fov = 60.0f;
	near = 0.1f;
	far = 1000.0f;
	this->aspectRatio = aspectRatio;
	this->clearColor = clearColor;
	// Set the clear color.
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}


Camera::~Camera() {}


void Camera::update() {
	// Manipulate the camera just like any other (model) object.
	// The view is just the inverse of the model.
	view = glm::inverse(gameObject->transform->model);

	// Makes the transform act like a normal transform
	// instead of backwards like the camera normally is.
	// Do this after the view has been calculated.
	gameObject->transform->model = glm::scale(gameObject->transform->model, glm::vec3(-gameObject->transform->scale.x, gameObject->transform->scale.y, -gameObject->transform->scale.z));

	
	// If the pitch and yaw angles are in degrees,
	// they need to be converted to radians.
	//float cosPitch = cos(glm::radians(-transform->rotation.x));
	//float sinPitch = sin(glm::radians(-transform->rotation.x));
	//float cosYaw = cos(glm::radians(transform->rotation.y));
	//float sinYaw = sin(glm::radians(transform->rotation.y));

	//glm::vec3 xaxis = { cosYaw, 0, -sinYaw };
	//glm::vec3 yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	//glm::vec3 zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

	//// Create a 4x4 view matrix from the right, up, forward and eye position vectors.
	//view = {
	//	xaxis.x, yaxis.x, zaxis.x, 0,
	//	xaxis.y, yaxis.y, zaxis.y, 0,
	//	xaxis.z, yaxis.z, zaxis.z, 0,
	//	-glm::dot(xaxis, transform->position), -glm::dot(yaxis, transform->position), -glm::dot(zaxis, transform->position), 1
	//};
	//transform->model = glm::inverse(view);


	projection = glm::perspective(
		fov,			// The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		aspectRatio,	// Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		near,			// Near clipping plane. Keep as big as possible, or you'll get precision issues.
		far);			// Far clipping plane. Keep as little as possible.


	ShaderManager::getInstance()->vp = projection * view;

}
