#include "Component.h"
using namespace lynx;


Component::Component(GameObject *gameObject) {
	this->gameObject = gameObject;
}


Component::~Component() {}
