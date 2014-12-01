#include "GameObject.h"
using namespace lynx;


GameObject::GameObject() {}

GameObject::GameObject(PrimitiveType _primitiveType, Shader *_shader, Texture *_texture) {
	shader = _shader;
	texture = _texture;

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
}


GameObject::~GameObject() {
	delete mesh;
	delete shader;
	delete texture;
	delete collider;
}


void GameObject::addChild(GameObject *_gameObject) {
	_gameObject->parent = this;
	children.push_back(_gameObject);
}



void GameObject::update() {

}



glm::vec3 GameObject::forward() {
	glm::mat4 view = glm::inverse(model);
	return glm::normalize(glm::vec3(view[0][2], view[1][2], view[2][2]));
}



glm::vec3 GameObject::left() {
	glm::mat4 view = glm::inverse(model);
	return glm::normalize(glm::vec3(view[0][0], view[1][0], view[2][0]));
}
