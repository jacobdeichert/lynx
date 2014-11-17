#pragma once
#include "GameObject.h"
// glm::translate, glm::rotate, glm::scale
#include <gtc/matrix_transform.hpp>

namespace Mammoth {
	class Camera : public GameObject {
	public:
		/*float left;
		float right;
		float bottom;
		float top;*/
		float near;
		float far;
		float fov;
		glm::vec3 direction;
		glm::vec3 up;
		glm::mat4 view;
		glm::mat4 projection;

		Camera();


		virtual ~Camera();


		void update();

		/**
		 * Override the GameObject's forward vector because in that function,
		 * the view matrix is calculated from the inverse of the model
		 * matrix since GameObjects don't have a view matrix. Cameras
		 * have a view matrix, so it saves one calculation by overriding.
		 *
		 * Virtual is optional here, but it is a good practice to
		 * remind the developer that it's overriding something.
		 */
		virtual glm::vec3 forward();

		/**
		* Override the GameObject's right vector because in that function,
		* the view matrix is calculated from the inverse of the model
		* matrix since GameObjects don't have a view matrix. Cameras
		* have a view matrix, so it saves one calculation by overriding.
		*/
		virtual glm::vec3 right();
	};
}
