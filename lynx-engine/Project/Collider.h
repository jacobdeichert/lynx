#pragma once
#include <vector>
#include <glm.hpp>

namespace lynx {
	class Collider {
	public:
		static const enum ColliderType { COLLIDER_TYPE_NONE, COLLIDER_TYPE_SPHERE, COLLIDER_TYPE_AA_BOX };
		ColliderType colliderType;
		Collider();
		virtual ~Collider();
		virtual bool checkCollision(Collider *collider) = 0;
		virtual bool checkCollision(std::vector<Collider*> colliders) = 0;
	};
}
