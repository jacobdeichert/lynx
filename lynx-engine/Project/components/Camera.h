#pragma once
#include "Component.h"
#include <gtc/matrix_transform.hpp>

namespace lynx {
	class Camera : public Component {
	public:
		float near;
		float far;
		float fov;
		float aspectRatio;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec4 clearColor;


		Camera(GameObject *gameObject, float aspectRatio, glm::vec4 clearColor);


		virtual ~Camera();


		virtual void update();
	};
}
