#include "BoxCollider.h"
using namespace lynx;



BoxCollider::BoxCollider(glm::vec3 _scale, glm::vec3 *_center) {
	scale = _scale;
	center = _center;
	colliderType = COLLIDER_TYPE_AABB;
}



BoxCollider::~BoxCollider() {}

