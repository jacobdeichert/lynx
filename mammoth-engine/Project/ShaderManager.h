#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <glm.hpp>
#include "GameObject.h"


namespace Mammoth {
	class ShaderManager {
	public:
		static ShaderManager* getInstance();


		void loadShader(std::string shaderNameID, std::string vertexShaderFile, std::string fragmentShaderFile);


		Shader* getShader(std::string shaderNameID);


		~ShaderManager();


		void render(GameObject *_gameObject, glm::mat4 _mvp);


	private:
		Shader* currentShader = nullptr;
		static ShaderManager* instance;
		std::map<std::string, Shader*> loadedShaders;

		ShaderManager();
	};
}
