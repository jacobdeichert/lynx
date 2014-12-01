#include "Ray.h"
using namespace lynx;



Ray::Ray() {}


Ray::Ray(glm::vec3 origin, glm::vec3 direction) {
	this->origin = origin;
	this->direction = glm::normalize(direction);
}


Ray::~Ray() {}


glm::vec3 Ray::getPoint(float distance) {
	return origin + direction * distance;
}



bool Ray::intersects(glm::vec3 position, float radius, float &distance) {
	glm::vec3 rayToSphereDir;
	float rayToSphereLength = 0.0f;
	float intersectPoint = 0.0f;
	float squaredPoint = 0.0f;

	rayToSphereDir = position - origin;
	rayToSphereLength = glm::dot(rayToSphereDir, rayToSphereDir);

	intersectPoint = glm::dot(rayToSphereDir, direction);

	if (intersectPoint < 0) {
		return false;
	}

	squaredPoint = (radius * radius) - rayToSphereLength + (intersectPoint * intersectPoint);

	if (squaredPoint < 0) {
		return false;
	}

	if (distance) {
		distance = intersectPoint - (float)sqrt(squaredPoint);
	}
	return true;
}
