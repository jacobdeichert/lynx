#pragma once
#include <vector>
#include <glm.hpp>
#include "MeshManager.h"

namespace lynx {
	class Collider {
	public:
		static const enum ColliderType { COLLIDER_TYPE_NONE, COLLIDER_TYPE_SPHERE, COLLIDER_TYPE_AA_BOX };
		ColliderType colliderType;
		glm::vec3 *position;
		Mesh *debugMesh;
		GLenum drawMode = GL_TRIANGLES;
		Collider();
		virtual ~Collider();
		virtual bool checkCollision(Collider *collider) = 0;
		virtual bool checkCollision(std::vector<Collider*> colliders) = 0;
	};
}
