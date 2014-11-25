#include "Collider.h"
using namespace lynx;




Collider::Collider() {}



Collider::~Collider() {
	delete position;
}
