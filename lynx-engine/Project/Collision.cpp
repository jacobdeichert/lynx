#include "Collision.h"
using namespace lynx;


Collision::Collision() {
}


Collision::Collision(bool _isCollision) {
	isCollision = _isCollision;
}


Collision::~Collision() {
}



//
//bool Collision::checkCollision(std::vector<Collider*> colliders) {
//	return false;
//}






Collision Collision::checkCollision(Collider *collider1, Collider *collider2) {
	// AABB
	if (collider1->colliderType == Collider::COLLIDER_TYPE_AABB) {
		// AABB > AABB
		if (collider2->colliderType == Collider::COLLIDER_TYPE_AABB) {
			return checkAABBToAABB(((BoxCollider*)collider1), ((BoxCollider*)collider2));
		} // AABB > SPHERE
		else if (collider2->colliderType == Collider::COLLIDER_TYPE_SPHERE) {
			return checkAABBToSphere(((BoxCollider*)collider1), ((SphereCollider*)collider2));
		}
	} // Sphere
	else if (collider1->colliderType == Collider::COLLIDER_TYPE_SPHERE) {
		// SPHERE > AABB
		if (collider2->colliderType == Collider::COLLIDER_TYPE_AABB) {
			return checkAABBToSphere(((BoxCollider*)collider2), ((SphereCollider*)collider1));
		} // SPHERE > SPHERE
		else if (collider2->colliderType == Collider::COLLIDER_TYPE_SPHERE) {
			return checkSphereToSphere(((SphereCollider*)collider1), ((SphereCollider*)collider2));
		}
	}
	return Collision(false);
}


Collision Collision::checkAABBToAABB(BoxCollider *box1, BoxCollider *box2) {
	if (abs(box1->center->x - box2->center->x) > (box1->scale.x + box2->scale.x) / 2) return Collision(false);
	if (abs(box1->center->y - box2->center->y) > (box1->scale.y + box2->scale.y) / 2) return Collision(false);
	if (abs(box1->center->z - box2->center->z) > (box1->scale.z + box2->scale.z) / 2) return Collision(false);
	// Otherwise there is an intersection.
	return Collision(true);
}



Collision Collision::checkAABBToSphere(BoxCollider *box, SphereCollider *sphere) {
	// Opposite corners of the cube.
	glm::vec3 corner1 = glm::vec3(box->center->x - box->scale.x / 2, box->center->y - box->scale.y / 2, box->center->z - box->scale.z / 2);
	glm::vec3 corner2 = glm::vec3(box->center->x + box->scale.x / 2, box->center->y + box->scale.y / 2, box->center->z + box->scale.z / 2);

	float distSquared = pow(sphere->radius, 2);
	if (sphere->center->x < corner1.x) distSquared -= pow(sphere->center->x - corner1.x, 2);
	else if (sphere->center->x > corner2.x) distSquared -= pow(sphere->center->x - corner2.x, 2);
	if (sphere->center->y < corner1.y) distSquared -= pow(sphere->center->y - corner1.y, 2);
	else if (sphere->center->y > corner2.y) distSquared -= pow(sphere->center->y - corner2.y, 2);
	if (sphere->center->z < corner1.z) distSquared -= pow(sphere->center->z - corner1.z, 2);
	else if (sphere->center->z > corner2.z) distSquared -= pow(sphere->center->z - corner2.z, 2);


	// If it's more, then there is an intersection.
	if (distSquared > 0) {
		return Collision(true);
	}
	return Collision(false);
}



Collision Collision::checkSphereToSphere(SphereCollider *sphere1, SphereCollider *sphere2) {
	glm::vec3 d = *sphere1->center - *sphere2->center;
	float distance = sqrt(pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2));

	// If the distance is less than both radii combined, there is a collision.
	if (distance <= sphere1->radius + sphere2->radius) {
		return Collision(true);
	}
	return Collision(false);
}

