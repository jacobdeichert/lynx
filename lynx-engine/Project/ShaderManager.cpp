#include "ShaderManager.h"
using namespace lynx;


ShaderManager* ShaderManager::instance = nullptr;

ShaderManager::ShaderManager() {
	std::string debugVertexGLSL = "#version 430 core \n"
		"uniform mat4 uni_mvp; \n"
		"layout(location = 0) in vec3 in_position; \n"
		"void main() { \n"
			"gl_Position = uni_mvp * vec4(in_position, 1); \n"
		"}";
	std::string debugFragmentGLSL = "#version 430 core \n"
		 "// Ouput data. \n"
		 "out vec4 out_color; \n"
		 "void main() { \n"
			"out_color = vec4(0, 1, 0, 1); \n"
		 "}";
	compileShader("LynxEngineDebugShader", debugVertexGLSL, debugFragmentGLSL);
}

ShaderManager::~ShaderManager() {}

ShaderManager* ShaderManager::getInstance() {
	if (instance == nullptr) instance = new ShaderManager();
	return instance;
}




std::string ShaderManager::getShaderCode(std::string filePath) {
	// Read the Vertex Shader code from the file
	std::string shaderCode;
	std::ifstream shaderStream(filePath, std::ios::in);
	if (shaderStream.is_open()) {
		std::string Line = "";
		while (getline(shaderStream, Line))
			shaderCode += "\n" + Line;
		shaderStream.close();
	}
	return shaderCode;
}


void ShaderManager::compileShader(std::string shaderNameID, std::string vertexShaderCode, std::string fragmentShaderCode) {
	// Ensure the shader hasn't already been loaded.
	if (loadedShaders.find(shaderNameID) == loadedShaders.end()) {
		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);


		GLint Result = GL_FALSE;
		int InfoLogLength;

		// Compile vertex shader.
		char const * VertexSourcePointer = vertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Check vertex shader.
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> VertexShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		fprintf(stdout, "%s", &VertexShaderErrorMessage[0]);

		// Compile fragment shader.
		char const * FragmentSourcePointer = fragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check fragment shader.
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		fprintf(stdout, "%s", &FragmentShaderErrorMessage[0]);

		// Link the program.
		GLuint programID = glCreateProgram();
		glAttachShader(programID, VertexShaderID);
		glAttachShader(programID, FragmentShaderID);
		glLinkProgram(programID);

		// Check the program.
		glGetProgramiv(programID, GL_LINK_STATUS, &Result);
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramErrorMessage(glm::max(InfoLogLength, int(1)));
		glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s", &ProgramErrorMessage[0]);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		// Add the shader to the loadedShaders list.
		loadedShaders[shaderNameID] = new Shader(shaderNameID, "LynxEngineDebugVertexShaderGLSL", "LynxEngineDebugFragmentShaderGLSL", programID);
	}
}


void ShaderManager::loadShader(std::string shaderNameID, std::string vertexShaderFilePath, std::string fragmentShaderFilePath) {
	compileShader(shaderNameID, getShaderCode(vertexShaderFilePath), getShaderCode(fragmentShaderFilePath));
}



Shader* ShaderManager::getShader(std::string shaderNameID) {
	return loadedShaders[shaderNameID];
}





void ShaderManager::render(GameObject *_gameObject, glm::mat4 _mvp) {
	/**
	 * Activate the shader if it isn't already the current one.
	 * 
	 * currentShader == _gameObject->shader results in true if they are the same,
	 * otherwise false.
	 */
	_gameObject->shader->activate(_gameObject->mesh, currentShader == _gameObject->shader);

	// Set this shader as the current shader.
	currentShader = _gameObject->shader;

	// Update all uniforms in the shader.
	_gameObject->shader->updateUniforms(_mvp);

	// Bind the VAO.
	// TODO: make a currentVAO and check if it's already bound.
	glBindVertexArray(_gameObject->mesh->vao);

	// Bind the texture.
	glBindTexture(GL_TEXTURE_2D, _gameObject->texture->textureID);

	// Activate wireframe mode if it's enabled for this object.
	if (_gameObject->isWireframeMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Draw the mesh using the specified draw mode.
	glDrawElements(_gameObject->drawMode, _gameObject->mesh->numElements, GL_UNSIGNED_INT, (void*)0);
	
	// Reactivate fill mode if this game object used wireframe mode.
	if (_gameObject->isWireframeMode) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Make sure we disable and unbind everything to prevent rendering issues later.
	/*
	glUseProgram(0);
	glBindVertexArray(0);
	*/
}

