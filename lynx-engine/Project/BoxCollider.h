#pragma once
#include "SphereCollider.h"

namespace lynx {
	class BoxCollider: public Collider {
	public:
		glm::vec3 scale;
		BoxCollider(glm::vec3 _scale, glm::vec3 *_position);
		virtual ~BoxCollider();
		virtual bool checkCollision(Collider *collider);
		virtual bool checkCollision(std::vector<Collider*> colliders);
	};
}
