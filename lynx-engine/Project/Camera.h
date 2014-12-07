#pragma once
#include "GameObject.h"
// glm::translate, glm::rotate, glm::scale
#include <gtc/matrix_transform.hpp>

namespace lynx {
	class Camera : public GameObject {
	public:
		float near;
		float far;
		float fov;
		float aspectRatio;
		//glm::vec3 direction;
		//glm::vec3 up;
		glm::mat4 view;
		glm::mat4 projection;

		Camera();


		Camera(float aspectRatio);


		virtual ~Camera();


		virtual void update();

		/**
		 * Override the GameObject's forward vector because in that function,
		 * the view matrix is calculated from the inverse of the model
		 * matrix since GameObjects don't have a view matrix. Cameras
		 * have a view matrix, so it saves one calculation by overriding.
		 *
		 * Virtual is optional here, but it is a good practice to
		 * remind the developer that it's overriding something.
		 */
		//virtual glm::vec3 forward();

		/**
		* Override the GameObject's left vector because in that function,
		* the view matrix is calculated from the inverse of the model
		* matrix since GameObjects don't have a view matrix. Cameras
		* have a view matrix, so it saves one calculation by overriding.
		*/
		//virtual glm::vec3 left();
	};
}
