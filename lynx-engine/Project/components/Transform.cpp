#include "Transform.h"
#include "../GameObject.h"
using namespace lynx;



Transform::Transform(GameObject *gameObject) : Component(gameObject) {
}


Transform::~Transform() {}


void Transform::update() {
	// Translate to the position relative to the parent model matrix.
	if (parent != nullptr) {
		if (parent->gameObject->name == "Main Camera") {
			model = glm::translate(parent->model, glm::vec3(-position.x, position.y, -position.z));
		}
		else {
			model = glm::translate(parent->model, position);
		}
	} // If there's no parent, use the identity matrix.
	else {
		model = glm::translate(glm::mat4(), position);
	}

	// Rotate each axis.
	if (parent != nullptr && parent->gameObject->name == "Main Camera") {
		model = glm::rotate(model, -rotation.x, glm::vec3(1, 0, 0));
		model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
		model = glm::rotate(model, -rotation.z, glm::vec3(0, 0, 1));
	}
	else {
		model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
		model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
		model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
	}

	// Scale the model.
	model = glm::scale(model, scale);
}


void Transform::addChild(Transform *transform) {
	transform->parent = this;
	children.push_back(transform);
}


glm::vec3 Transform::forward() {
	if (gameObject->name == "Main Camera") return -glm::normalize(glm::vec3(model[2][0], model[2][1], model[2][2]));
	return glm::normalize(glm::vec3(model[2][0], model[2][1], model[2][2]));
}


glm::vec3 Transform::left() {
	if (gameObject->name == "Main Camera") return -glm::normalize(glm::vec3(model[0][0], model[0][1], model[0][2]));
	return glm::normalize(glm::vec3(model[0][0], model[0][1], model[0][2]));
}


void Transform::setPosition(glm::vec3 position) {
	this->position = position;
}


void Transform::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}


void Transform::translate(glm::vec3 translation) {
	position += translation;
}


void Transform::translate(float x, float y, float z) {
	position += glm::vec3(x, y, z);
}


void Transform::setRotation(glm::vec3 rotation) {
	this->rotation = rotation;
}


void Transform::setRotation(float x, float y, float z) {
	rotation = glm::vec3(x, y, z);
}


void Transform::rotate(glm::vec3 rotation) {
	this->rotation += rotation;
}


void Transform::rotate(float x, float y, float z) {
	rotation += glm::vec3(x, y, z);
}


void Transform::setScale(glm::vec3 scale) {
	this->scale = scale;
}


void Transform::setScale(float xyz) {
	scale = glm::vec3(xyz);
}


void Transform::setScale(float x, float y, float z) {
	scale = glm::vec3(x, y, z);
}
