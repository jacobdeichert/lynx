#include "SphereCollider.h"
using namespace lynx;


SphereCollider::SphereCollider(float _radius, glm::vec3 *_center) {
	radius = _radius;
	center = _center;
	colliderType = COLLIDER_TYPE_SPHERE;
}


SphereCollider::~SphereCollider() {}

