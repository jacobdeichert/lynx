#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <glm.hpp>
#include "GameObject.h"


namespace lynx {
	class ShaderManager {
	public:
		static ShaderManager* getInstance();


		void loadShader(std::string shaderNameID, std::string vertexShaderFilePath, std::string fragmentShaderFilePath);


		Shader* getShader(std::string shaderNameID);


		~ShaderManager();


		std::string getShaderCode(std::string filePath);


		void render(GameObject *_gameObject, glm::mat4 _mvp);


	private:
		Shader* currentShader = nullptr;
		static ShaderManager* instance;
		std::map<std::string, Shader*> loadedShaders;

		ShaderManager();


		void compileShader(std::string shaderNameID, std::string vertexShaderCode, std::string fragmentShaderCode);
	};
}
