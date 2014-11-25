#pragma once
#include "SphereCollider.h"

namespace lynx {
	class BoxCollider: public Collider {
	public:
		glm::vec3 scale;
		BoxCollider(glm::vec3 _scale, glm::vec3 *_center);
		virtual ~BoxCollider();
	};
}
