#include "Transform.h"
#include "../GameObject.h"
using namespace lynx;



Transform::Transform(GameObject *gameObject) : Component(gameObject) {
}


Transform::~Transform() {}


void Transform::update() {
	// Translate to the position relative to the parent model matrix.
	if (parent != nullptr) {
		model = glm::translate(parent->model, position);
	} // If there's no parent, use the identity matrix.
	else {
		model = glm::translate(glm::mat4(), position);
	}


	// Rotate the model.
	if (gameObject->name == "Main Camera") {
		model *= anglesToAxes();
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


glm::vec3 Transform::left() {
	return glm::normalize(glm::vec3(model[0][0], model[0][1], model[0][2]));
}


glm::vec3 Transform::up() {
	return glm::normalize(glm::vec3(model[1][0], model[1][1], model[1][2]));
}


glm::vec3 Transform::forward() {
	return glm::normalize(glm::vec3(model[2][0], model[2][1], model[2][2]));
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


///////////////////////////////////////////////////////////////////////////////
// convert Euler angles(x,y,z) to axes(left, up, forward)
// Each column of the rotation matrix represents left, up and forward axis.
// The order of rotation is Roll->Yaw->Pitch (Rx*Ry*Rz)
// Rx: rotation about X-axis, pitch
// Ry: rotation about Y-axis, yaw(heading)
// Rz: rotation about Z-axis, roll
//    Rx           Ry          Rz
// |1  0   0| | Cy  0 Sy| |Cz -Sz 0|   | CyCz        -CySz         Sy  |
// |0 Cx -Sx|*|  0  1  0|*|Sz  Cz 0| = | SxSyCz+CxSz -SxSySz+CxCz -SxCy|
// |0 Sx  Cx| |-Sy  0 Cy| | 0   0 1|   |-CxSyCz+SxSz  CxSySz+SxCz  CxCy|
///////////////////////////////////////////////////////////////////////////////
glm::mat4 Transform::anglesToAxes() {
	// TODO: wrap my head around this.
	const float DEG2RAD = 3.141593f / 180;
	float sx, sy, sz, cx, cy, cz, theta;

	// Rotation angle about X-axis (pitch).
	theta = rotation.x * DEG2RAD;
	sx = sinf(theta);
	cx = cosf(theta);

	// Rotation angle about Y-axis (yaw).
	theta = -rotation.y * DEG2RAD;
	sy = sinf(theta);
	cy = cosf(theta);

	// Rotation angle about Z-axis (roll).
	theta = rotation.z * DEG2RAD;
	sz = sinf(theta);
	cz = cosf(theta);

	// Determine left axis.
	glm::vec3 left;
	left.x = cy*cz;
	left.y = sx*sy*cz + cx*sz;
	left.z = -cx*sy*cz + sx*sz;

	// Determine up axis.
	glm::vec3 up;
	up.x = -cy*sz;
	up.y = -sx*sy*sz + cx*cz;
	up.z = cx*sy*sz + sx*cz;

	// Determine forward axis.
	glm::vec3 forward;
	forward.x = sy;
	forward.y = -sx*cy;
	forward.z = cx*cy;

	// Combine them.
	glm::mat4 m = {
		left.x, up.x, forward.x, 0,
		left.y, up.y, forward.y, 0,
		left.z, up.z, forward.z, 0,
		0, 0, 0, 1
	};

	return m;
}
