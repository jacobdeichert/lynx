#include "Camera.h"
#include "../GameObject.h"
#include "../ShaderManager.h"
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
	// Manipulate the camera transform just like any other (model) object.
	// The view is just the inverse of the model.
	view = glm::inverse(gameObject->transform->model);


	// Flip the x and z scale. Makes the transform act like a normal
	// transform instead of backwards like the camera normally is.
	// Do this after the view has been calculated.
	gameObject->transform->model = glm::scale(gameObject->transform->model, glm::vec3(-gameObject->transform->scale.x, gameObject->transform->scale.y, -gameObject->transform->scale.z));


	projection = glm::perspective(
		fov,			// The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		aspectRatio,	// Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		near,			// Near clipping plane. Keep as big as possible, or you'll get precision issues.
		far);			// Far clipping plane. Keep as little as possible.

	ShaderManager::getInstance()->projection = projection;
	ShaderManager::getInstance()->view = view;
}
