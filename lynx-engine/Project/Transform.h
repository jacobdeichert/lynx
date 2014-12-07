#pragma once
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Component.h"

namespace lynx {
	class Transform : public Component {
	public:
		Transform *parent = nullptr;
		glm::mat4 model = glm::mat4();
		glm::vec3 position = glm::vec3(0);
		glm::vec3 rotation = glm::vec3(0);
		glm::vec3 scale = glm::vec3(1);
		std::vector<Transform*> children;



		Transform(GameObject *gameObject);



		virtual ~Transform();



		virtual void update();



		void addChild(Transform *transform);



		glm::vec3 forward();



		glm::vec3 left();
	};
}

