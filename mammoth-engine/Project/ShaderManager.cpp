#include "ShaderManager.h"
using namespace Mammoth;


ShaderManager* ShaderManager::instance = nullptr;

ShaderManager::ShaderManager() {}

ShaderManager::~ShaderManager() {}

ShaderManager* ShaderManager::getInstance() {
	if (instance == nullptr) instance = new ShaderManager();
	return instance;
}





void ShaderManager::loadShader(std::string shaderNameID, std::string vertexShaderFile, std::string fragmentShaderFile) {
	// Ensure the shader hasn't already been loaded.
	if (loadedShaders.find(shaderNameID) == loadedShaders.end()) {

		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Read the Vertex Shader code from the file
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertexShaderFile, std::ios::in);
		if (VertexShaderStream.is_open())
		{
			std::string Line = "";
			while (getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}

		// Read the Fragment Shader code from the file
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragmentShaderFile, std::ios::in);
		if (FragmentShaderStream.is_open()){
			std::string Line = "";
			while (getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}

		GLint Result = GL_FALSE;
		int InfoLogLength;

		// Compile Vertex Shader
		printf("Compiling shader : %s\n", vertexShaderFile.c_str());
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> VertexShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

		// Compile Fragment Shader
		printf("Compiling shader : %s\n", fragmentShaderFile.c_str());
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

		// Link the program
		fprintf(stdout, "Linking program\n");
		GLuint programID = glCreateProgram();
		glAttachShader(programID, VertexShaderID);
		glAttachShader(programID, FragmentShaderID);
		glLinkProgram(programID);

		// Check the program
		glGetProgramiv(programID, GL_LINK_STATUS, &Result);
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramErrorMessage(glm::max(InfoLogLength, int(1)));
		glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		loadedShaders[shaderNameID] = new Shader(shaderNameID, vertexShaderFile, fragmentShaderFile, programID);
	}
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

	// Draw the mesh using the specified draw mode.
	glDrawElements(_gameObject->drawMode, _gameObject->mesh->numElements, GL_UNSIGNED_INT, (void*)0);


	// Make sure we disable and unbind everything to prevent rendering issues later.
	/*
	glUseProgram(0);
	glBindVertexArray(0);
	*/
}

