#pragma once
#include <vector>
#include <glm.hpp>

namespace lynx {
	// Forward declaration, to prevent include loops.
	class GameObject;

	class Collider {
	public:
		static const enum ColliderType { COLLIDER_TYPE_NONE, COLLIDER_TYPE_SPHERE, COLLIDER_TYPE_AA_BOX };
		ColliderType colliderType;
		GameObject *parent = nullptr;
		Collider();
		virtual ~Collider();
		virtual bool checkCollision(Collider *collider) = 0;
		virtual bool checkCollision(std::vector<Collider*> colliders) = 0;
	};
}
