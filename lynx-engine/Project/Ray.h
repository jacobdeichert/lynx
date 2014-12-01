#pragma once
#include <glm.hpp>

namespace lynx {
	class Ray {
	public:
		glm::vec3 origin;

		glm::vec3 direction;

		Ray();


		Ray(glm::vec3 origin, glm::vec3 direction);


		~Ray();


		/**
		 * Return a point that is a certain distance along the ray.
		 */
		glm::vec3 getPoint(float distance);

		bool intersects(glm::vec3 position, float radius, float &distance);
	};
}

