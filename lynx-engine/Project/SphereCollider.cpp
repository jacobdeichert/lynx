#include "SphereCollider.h"
using namespace lynx;


SphereCollider::SphereCollider(float _radius, glm::vec3 *_position) {
	radius = _radius;
	position = _position;
	debugMesh = MeshManager::getInstance()->get("models/sphere.ply");
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