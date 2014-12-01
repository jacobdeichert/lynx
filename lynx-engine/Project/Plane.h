#pragma once
#include <glm.hpp>


namespace lynx {
	class Plane
	{
	public:
		float distance;
		glm::vec3 normal;

		Plane();
		Plane(glm::vec3 normal, float distance);
		~Plane();

		/**
		 * Returns:
		 * > 0 if the point lies in front of the plane
		 * < 0 if the point lies behind the plane
		 * 0 if the point lies on the plane.
		 *
		 * The signed distance from the point to the plane is returned.
		 */
		float dot(glm::vec3 point);
	};
}
