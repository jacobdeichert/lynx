#pragma once
#include <GL/glew.h>
#include <string>
#include <map>
#include <FreeImage.h>
#include "Texture.h"
#include "Logger.h"


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
