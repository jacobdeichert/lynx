#pragma once
#include <map>
#include <glm.hpp>
#include "Shader.h"


namespace lynx {
	class ShaderManager {
	public:
		Shader* currentShader = nullptr;
		// The camera projection and view.
		// TODO: move this somewhere better??
		glm::mat4 view;
		glm::mat4 projection;


		static ShaderManager* getInstance();


		~ShaderManager();


	private:
		static ShaderManager* instance;

		ShaderManager();


	};
}
