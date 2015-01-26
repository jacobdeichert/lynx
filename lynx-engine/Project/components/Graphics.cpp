#include "Graphics.h"
#include "../Mesh.h"
#include "../Shader.h"
#include "../Texture.h"
#include "../ShaderManager.h"
#include "../Scene.h"
#include "../GameObject.h"
using namespace lynx;



Graphics::Graphics(GameObject *gameObject, Mesh *mesh, Shader *shader, Texture *texture, GLenum drawMode) : Component(gameObject) {
	this->mesh = mesh;
	this->shader = shader;
	this->texture = texture;
	this->drawMode = drawMode;
}


Graphics::~Graphics() {
	delete mesh;
	delete texture;
	delete shader;
}


void Graphics::update() {
	// If there is a mesh (prevents camera model from being updated here).
	if (mesh != nullptr) {
		/**
		 * Activate the shader if it isn't already the current one.
		 *
		 * (ShaderManager::getInstance()->currentShader == shader) results in true if they are the same.
		 */
		shader->activate(mesh, ShaderManager::getInstance()->currentShader == shader);

		// Set this shader as the current shader.
		ShaderManager::getInstance()->currentShader = shader;

		// Update all uniforms in the shader.
		shader->updateUniforms(ShaderManager::getInstance()->projection,
			ShaderManager::getInstance()->view,
			gameObject->transform->model);

		// Bind the VAO.
		// TODO: make a currentVAO and check if it's already bound.
		glBindVertexArray(mesh->vao);

		// Bind the texture if there is one.
		if (texture != nullptr) glBindTexture(GL_TEXTURE_2D, texture->textureID);

		// Activate wireframe mode if it's enabled for this object.
		if (isWireframeMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// Draw the mesh using the specified draw mode.
		glDrawElements(drawMode, mesh->numElements, GL_UNSIGNED_INT, (void*)0);

		// Reactivate fill mode if this game object used wireframe mode.
		if (isWireframeMode) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Make sure we disable and unbind everything to prevent rendering issues later.
		/*
		glUseProgram(0);
		glBindVertexArray(0);
		*/
	}

}
