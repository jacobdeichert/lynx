#include "Resources.h"
#include "Texture.h"
#include "Mesh.h"
using namespace lynx;

//================================================================================================
// Private
//================================================================================================

namespace {


}

//================================================================================================
// Public
//================================================================================================

void Resources::init() {
}

Texture* Resources::getTexture(std::string filepath) {

	return new Texture(filepath, 0);
}


Mesh* Resources::getMesh(std::string filepath) {

}