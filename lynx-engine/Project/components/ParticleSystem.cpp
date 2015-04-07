#include "ParticleSystem.h"
#include "../GameObject.h"
#include "../Resources.h"
#include <gtc/random.hpp>
using namespace lynx;


ParticleSystem::ParticleSystem(GameObject *gameObject, int numParticles, bool isRandom, glm::vec3 color) : Component(gameObject) {
	std::vector<GLfloat> vertices;
	std::vector<GLuint> elements;

	// Load the particle shader. That method also ensures it's not loaded multiple times.
	Resources::loadShader("particle", "LynxEngine/shaders/particle_vert.glsl", "LynxEngine/shaders/particle_frag.glsl");

	// Create a mesh for the particle system.
	for (int i = 0; i < numParticles * 11; i += 11) {
		// vertex pos    normal     uv       color
		// 1, 1, 0,      0, 1, 0,   0, 1,    1, 1, 1

		// vertex positions are zero
		vertices.push_back(0);
		vertices.push_back(0);
		vertices.push_back(0);

		// use random normals so that the particles travel in random directions
		glm::vec3 r = glm::sphericalRand<float>(1.0f);
		vertices.push_back(r.x);
		vertices.push_back(r.y);
		vertices.push_back(r.z);

		// use uv.u as the random speed factor for each particle
		vertices.push_back(glm::linearRand(10.0f, 100.0f));
		vertices.push_back(0); // just set uv.v to zero because it isn't used

		// give them color values
		if (isRandom) {
			// Use random color values.
			vertices.push_back(glm::linearRand<float>(0, 1.0f));
			vertices.push_back(glm::linearRand<float>(0, 1.0f));
			vertices.push_back(glm::linearRand<float>(0, 1.0f));
		}
		else {
			// Use the specified color.
			vertices.push_back(color.r);
			vertices.push_back(color.g);
			vertices.push_back(color.b);
		}
	}

	// Create an element index for each particle.
	for (int j = 0; j < numParticles; j++) {
		elements.push_back(j);
	}

	// Create the mesh.
	Resources::createMesh(gameObject->name, vertices, elements);

	// Create the game object.
	gameObject->addComponent(new Graphics(gameObject, Resources::getMesh(gameObject->name), Resources::getShader("particle"), nullptr, GL_POINTS));
}


ParticleSystem::~ParticleSystem() {}


void ParticleSystem::update() {

}
