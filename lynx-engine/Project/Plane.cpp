#include "Plane.h"
using namespace lynx;


Plane::Plane() {}

Plane::Plane(glm::vec3 normal, float distance) {
	this->normal = glm::normalize(normal);
	this->distance = distance;
}


Plane::~Plane() {}


float Plane::dot(glm::vec3 point) {
	return glm::dot(normal, point) + distance;
}