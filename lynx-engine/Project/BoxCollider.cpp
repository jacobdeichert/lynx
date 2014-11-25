#include "BoxCollider.h"
using namespace lynx;



BoxCollider::BoxCollider(glm::vec3 _scale, glm::vec3 *_center) {
	scale = _scale;
	center = _center;
	colliderType = COLLIDER_TYPE_AABB;
}



BoxCollider::~BoxCollider() {}



bool BoxCollider::checkCollision(Collider *collider) {
	if (collider->colliderType == COLLIDER_TYPE_AABB) {
		return checkAABB(collider);
	}
	else if (collider->colliderType == COLLIDER_TYPE_SPHERE) {
		return checkSphere(collider);
	}
	return false;
}



bool BoxCollider::checkCollision(std::vector<Collider*> colliders) {
	return false;
}



bool BoxCollider::checkAABB(Collider *collider) {
	if (abs(center->x - collider->center->x) > (scale.x + ((BoxCollider*)collider)->scale.x) / 2) return false;
	if (abs(center->y - collider->center->y) > (scale.y + ((BoxCollider*)collider)->scale.y) / 2) return false;
	if (abs(center->z - collider->center->z) > (scale.z + ((BoxCollider*)collider)->scale.z) / 2) return false;
	printf("cube > cube collision     %f\n", center->x + center->y + center->z);
	// Otherwise there is an intersection.
	return true;
}



bool BoxCollider::checkSphere(Collider *collider) {
	glm::vec3 corner1 = glm::vec3(center->x - scale.x / 2, center->y - scale.y / 2, center->z - scale.z / 2);
	glm::vec3 corner2 = glm::vec3(center->x + scale.x / 2, center->y + scale.y / 2, center->z + scale.z / 2);

	float distSquared = pow(((SphereCollider*)collider)->radius, 2);
	/* assume C1 and C2 are element-wise sorted, if not, do that now */
	if (collider->center->x < corner1.x) distSquared -= pow(collider->center->x - corner1.x, 2);
	else if (collider->center->x > corner2.x) distSquared -= pow(collider->center->x - corner2.x, 2);
	if (collider->center->y < corner1.y) distSquared -= pow(collider->center->y - corner1.y, 2);
	else if (collider->center->y > corner2.y) distSquared -= pow(collider->center->y - corner2.y, 2);
	if (collider->center->z < corner1.z) distSquared -= pow(collider->center->z - corner1.z, 2);
	else if (collider->center->z > corner2.z) distSquared -= pow(collider->center->z - corner2.z, 2);
	
	if (distSquared > 0) printf("cube > sphere collision     %f\n", center->x + center->y + center->z);

	return distSquared > 0;
}
