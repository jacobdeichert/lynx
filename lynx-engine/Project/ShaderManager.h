#pragma once
#include <map>
#include <glm.hpp>
#include "components\Graphics.h"


namespace lynx {
	class ShaderManager {
	public:
		Shader* currentShader = nullptr;
		// The camera projection * view.
		// TODO: move this somewhere better??
		glm::mat4 vp; 


		static ShaderManager* getInstance();


		void loadShader(std::string shaderNameID, std::string vertexShaderFilePath, std::string fragmentShaderFilePath);


		Shader* getShader(std::string shaderNameID);


		~ShaderManager();


		std::string getShaderCode(std::string filePath);


	private:
		static ShaderManager* instance;
		std::map<std::string, Shader*> loadedShaders;

		ShaderManager();


		void compileShader(std::string shaderNameID, std::string vertexShaderCode, std::string fragmentShaderCode);
	};
}
