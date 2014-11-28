#include "Ray.h"

namespace lynx {

Ray::Ray() {}


Ray::Ray(glm::vec3 origin, glm::vec3 direction) {
	this->origin = origin;
	this->direction = glm::normalize(direction);
}


Ray::~Ray() {}


glm::vec3 Ray::getPoint(float distance) {
	return origin + direction * distance;
}

}
