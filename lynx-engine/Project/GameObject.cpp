#include "GameObject.h"
#include "ShaderManager.h"
using namespace lynx;


GameObject::GameObject() {
	transform = new Transform(this);
}

GameObject::GameObject(PrimitiveType _primitiveType, Shader *_shader, Texture *_texture) {
	shader = _shader;
	texture = _texture;
	transform = new Transform(this);

	// Initialize the primitive model
	if (_primitiveType == PRIMITIVE_TRIANGLE) {
		mesh = MeshManager::getInstance()->get("PRIMITIVE_TRIANGLE");
		drawMode = GL_TRIANGLES;
	}
	else if (_primitiveType == PRIMITIVE_QUAD) {
		mesh = MeshManager::getInstance()->get("PRIMITIVE_QUAD");
		drawMode = GL_TRIANGLE_FAN;
	}
}

GameObject::GameObject(Mesh *_mesh, Shader *_shader, Texture *_texture) {
	mesh = _mesh;
	shader = _shader;
	texture = _texture;
	drawMode = GL_TRIANGLES;
	transform = new Transform(this);
}


GameObject::~GameObject() {
	delete mesh;
	delete shader;
	delete texture;
	delete collider;
	delete transform;
}



void GameObject::update(glm::mat4 vp) {
	transform->update();

	// If there is a mesh (prevents camera model from being updated here).
	if (mesh != nullptr) {
		// Render the object with the mvp (model, view, projection matrix)
		ShaderManager::getInstance()->render(this, vp * transform->model);
	}

	// Move to a Physics component?
	// Render the collider with the mvp if there is one.
	//if (collider != nullptr && collider->isRender) {
	//	// Calculate position and scale for collider model. Ignore rotation.
	//	glm::mat4 colliderModel = glm::translate(glm::mat4(), transform->position);

	//	switch (collider->colliderType) {
	//	case Collider::COLLIDER_TYPE_SPHERE:
	//		sphereColliderVisual->transform->scale = glm::vec3(((SphereCollider*)collider)->radius * 2);
	//		colliderModel = glm::scale(colliderModel, sphereColliderVisual->transform->scale);
	//		ShaderManager::getInstance()->render(sphereColliderVisual, _vp * colliderModel);
	//		break;
	//	case Collider::COLLIDER_TYPE_AABB:
	//		boxColliderVisual->transform->scale = ((BoxCollider*)i->collider)->scale;
	//		colliderModel = glm::scale(colliderModel, boxColliderVisual->transform->scale);
	//		ShaderManager::getInstance()->render(boxColliderVisual, _vp * colliderModel);
	//		break;
	//	}
	//}

	// Update any children.
	for (auto &i : transform->children) {
		i->gameObject->update(vp);
	}
}


