#pragma once
#include "Collider.h"

namespace lynx {
	class SphereCollider : public Collider {
	public:
		float radius;
		glm::vec3 *position = nullptr;
		SphereCollider(float _radius, glm::vec3 *_position);
		virtual ~SphereCollider();
		virtual bool checkCollision(Collider *collider);
		virtual bool checkCollision(std::vector<Collider*> colliders);
	};
}
