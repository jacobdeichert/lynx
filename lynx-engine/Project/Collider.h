#pragma once
#include <vector>
#include <glm.hpp>
#include "MeshManager.h"

namespace lynx {
	class Collider {
	public:
		static const enum ColliderType { COLLIDER_TYPE_NONE, COLLIDER_TYPE_SPHERE, COLLIDER_TYPE_AABB };
		ColliderType colliderType;

		/**
		 * Pointer to the position of the parent.
		 */
		glm::vec3 *center;

		bool isRender = false;
		Collider();
		virtual ~Collider();
	};
}
