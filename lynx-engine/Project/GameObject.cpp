#include "GameObject.h"
using namespace lynx;


GameObject::GameObject(std::string name) {
	this->name = name;
}

//GameObject::GameObject(Graphics *graphics) {
	//GameObject();
	//this->graphics = graphics;

	//shader = _shader;
	//texture = _texture;

	//// Initialize the primitive model
	//if (_primitiveType == PRIMITIVE_TRIANGLE) {
	//	mesh = MeshManager::getInstance()->get("PRIMITIVE_TRIANGLE");
	//	drawMode = GL_TRIANGLES;
	//}
	//else if (_primitiveType == PRIMITIVE_QUAD) {
	//	mesh = MeshManager::getInstance()->get("PRIMITIVE_QUAD");
	//	drawMode = GL_TRIANGLE_FAN;
	//}
//}
//
//GameObject::GameObject(Mesh *_mesh, Shader *_shader, Texture *_texture) {
//	GameObject();
//	mesh = _mesh;
//	shader = _shader;
//	texture = _texture;
//}


GameObject::~GameObject() {
	delete collider;
	delete transform;
	delete graphics;
	delete camera;
}


void GameObject::addComponent(Component *c) {
	//printf("%s", typename(c));
}


void GameObject::addComponent(Graphics *g) {
	//printf("%s", typename(c));
	graphics = g;
}


void GameObject::addComponent(Camera *c) {
	camera = c;
}


void GameObject::update() {
	transform->update();
	if (camera) camera->update();
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
		i->gameObject->update();
	}
}



void GameObject::render() {
	// If this has a graphics component, then render it.
	if (graphics) graphics->update();
	// Render any children.
	for (auto &i : transform->children) {
		i->gameObject->render();
	}
}
