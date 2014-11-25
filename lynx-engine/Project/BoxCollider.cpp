#include "BoxCollider.h"
using namespace lynx;


BoxCollider::BoxCollider(glm::vec3 _scale, glm::vec3 *_position) {
	scale = _scale;
	position = _position;
	colliderType = COLLIDER_TYPE_AA_BOX;
}


BoxCollider::~BoxCollider() {}


bool BoxCollider::checkCollision(Collider *collider) {
	if (collider->colliderType == COLLIDER_TYPE_AA_BOX) {
		
	}
	return false;
}

bool BoxCollider::checkCollision(std::vector<Collider*> colliders) {
	return false;
}