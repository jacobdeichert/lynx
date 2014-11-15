#include "Shader.h"


Shader::Shader(std::string _name, std::string _vertexFile, std::string _fragmentFile, GLuint _programID) {
	name = _name;
	vertexFile = _vertexFile;
	fragmentFile = _fragmentFile;
	programID = _programID;
	uniformMVP = glGetUniformLocation(programID, "uni_mvp");
	uniformTexture = glGetUniformLocation(programID, "uni_texture");
	attributePosition = glGetAttribLocation(programID, "in_position");
	attributeNormal = glGetAttribLocation(programID, "in_normal");
	attributeUV = glGetAttribLocation(programID, "in_uv");
	attributeColor = glGetAttribLocation(programID, "in_color");


	/**
	* Now bind the uniform samplers to the corresponding texture units.
	* Note that we must bind the uniform samplers to the texture unit,
	* not the texture object ID!
	*
	* This so far only needs to be called once...
	*/
	glActiveTexture(GL_TEXTURE0);	// Set the active texture unit.
	glUniform1i(uniformTexture, 0);	// Bind the first sampler to texture unit 0.
	//glUniform1i(uniformTex1, 1);	// Bind the second sampler to texture unit 1.
	//glUniform1i(uniformTex2, 2);	// Bind the third sampler to texture unit 2.
}


Shader::~Shader() {}


void Shader::activate(Mesh *_mesh, bool isCurrentShader) {
	// TODO: currently, I never deactivate a shader.. probably 
	// should be controlled from shaderManager.


	// Tell the GPU to start using this shader program if it isn't already.
	if (!isCurrentShader) {
		glUseProgram(programID);
	}

	/**
	* Activate the attributes of the VBO if the mesh hasn't already
	* had them activated for their shader.
	*/
	if (_mesh->activeShaderID != programID) {
		_mesh->activeShaderID = programID;

		//printf("mesh activated: %s \n", name.c_str());
		// Bind the mesh VAO and VBO before activating the attributes.
		glBindVertexArray(_mesh->vao);
		glBindBuffer(GL_ARRAY_BUFFER, _mesh->vbo);


		GLuint numParts = 11;
		// Each vertex in my vbo consists of numParts floats	(numParts * sizeof(GLfloat))
		glVertexAttribPointer(attributePosition, 3, GL_FLOAT, GL_FALSE, numParts * sizeof(GLfloat), 0);
		// The normal values are 3 values into the numParts
		glVertexAttribPointer(attributeNormal, 3, GL_FLOAT, GL_FALSE, numParts * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		// The UV values are 6 values into the numParts
		glVertexAttribPointer(attributeUV, 2, GL_FLOAT, GL_FALSE, numParts * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
		// The color values are 8 values into the numParts
		glVertexAttribPointer(attributeColor, 3, GL_FLOAT, GL_FALSE, numParts * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));


		// TODO: should disable these after glDrawElements(...) as a good habit...?
		glEnableVertexAttribArray(attributePosition);
		glEnableVertexAttribArray(attributeNormal);
		glEnableVertexAttribArray(attributeUV);
		glEnableVertexAttribArray(attributeColor);

	}
}


void Shader::updateUniforms(glm::mat4 _mvp) {
	// Send uniforms to the shader.
	glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, glm::value_ptr(_mvp));
}
