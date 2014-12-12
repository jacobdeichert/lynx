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


		glm::vec3 left();
		glm::vec3 up();
		glm::vec3 forward();


		void setPosition(glm::vec3 position);
		void setPosition(float x, float y, float z);
		void translate(glm::vec3 translation);
		void translate(float x, float y, float z);


		void setRotation(glm::vec3 rotation);
		void setRotation(float x, float y, float z);
		void rotate(glm::vec3 rotation);
		void rotate(float x, float y, float z);


		void setScale(glm::vec3 scale);
		void setScale(float xyz);
		void setScale(float x, float y, float z);
	};
}

