#pragma once
#include "Collider.h"

namespace lynx {
	class SphereCollider : public Collider {
	public:
		float radius;
		SphereCollider(float _radius, GameObject *_parent);
		virtual ~SphereCollider();
		virtual bool checkCollision(Collider *collider);
		virtual bool checkCollision(std::vector<Collider*> colliders);
	};
}
