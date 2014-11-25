#include "SphereCollider.h"
using namespace lynx;


SphereCollider::SphereCollider(float _radius, GameObject *_parent) {
	radius = _radius;
	parent = _parent;
	colliderType = COLLIDER_TYPE_SPHERE;
}


SphereCollider::~SphereCollider() {}


bool SphereCollider::checkCollision(Collider *collider) {
	if (collider->colliderType == COLLIDER_TYPE_SPHERE) {
	}
	return true;
}

bool SphereCollider::checkCollision(std::vector<Collider*> colliders) {
	return true;
}