#pragma once
// Include GLEW. Always include it before gl.h and glfw.h
#include <GL/glew.h>
#include <string>

namespace lynx {
	class Texture {
	public:
		GLuint textureID;
		Texture(std::string _filePath, GLuint _textureID);
		~Texture();
	private:
		std::string filePath;
	};
}
