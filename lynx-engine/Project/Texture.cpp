#include "Texture.h"
using namespace lynx;

Texture::Texture(std::string _filePath, GLuint _textureID) {
	filePath = _filePath;
	textureID = _textureID;
}


Texture::~Texture() {}
