#include "Texture.h"


Texture::Texture(std::string _name, GLuint _textureID) {
	name = _name;
	textureID = _textureID;
}


Texture::~Texture() {}
