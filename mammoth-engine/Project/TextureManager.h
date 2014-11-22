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
		void load(std::string textureNameID, std::string filePath);
		Texture* get(std::string textureNameID);
	private:
		std::map<std::string, Texture*> loadedTextures;
		static TextureManager* instance;
		TextureManager();
	};
}
