#include "ShaderManager.h"
#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <glm.hpp>
#include "Log.h"
#include "Shader.h"
using namespace lynx;


ShaderManager* ShaderManager::instance = nullptr;


ShaderManager::ShaderManager() {}


ShaderManager::~ShaderManager() {
	delete instance;
}


ShaderManager* ShaderManager::getInstance() {
	if (instance == nullptr) instance = new ShaderManager();
	return instance;
}





