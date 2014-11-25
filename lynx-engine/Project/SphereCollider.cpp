#include "SphereCollider.h"
using namespace lynx;


SphereCollider::SphereCollider(float _radius, glm::vec3 *_position) {
	radius = _radius;
	position = _position;
	colliderType = COLLIDER_TYPE_SPHERE;
}


SphereCollider::~SphereCollider() {}


bool SphereCollider::checkCollision(Collider *collider) {
	if (collider->colliderType == COLLIDER_TYPE_SPHERE) {
		glm::vec3 d = *position - *collider->position;
		float distance = sqrt(pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2));

		// If the distance is less than both radii combined, there is a collision.
		if (distance <= ((SphereCollider*)collider)->radius + radius) {
			return true;
		}
	}
	return false;
}

bool SphereCollider::checkCollision(std::vector<Collider*> colliders) {
	return true;
}