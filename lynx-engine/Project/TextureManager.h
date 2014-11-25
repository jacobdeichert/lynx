#pragma once
// Include GLEW. Always include it before gl.h and glfw.h
#include <GL/glew.h>
#include <string>
#include <map>
// image loader library
#include <FreeImage.h>
#include "Texture.h"


namespace lynx {
	class TextureManager {
	public:
		~TextureManager();
		static TextureManager* getInstance();
		Texture* get(std::string _textureFilePath);
	private:
		std::map<std::string, Texture*> loadedTextures;
		static TextureManager* instance;
		TextureManager();
		void load(std::string _textureFilePath);
	};
}
