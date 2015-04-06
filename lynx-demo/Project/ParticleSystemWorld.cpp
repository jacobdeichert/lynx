#include "ParticleSystemWorld.h"
#include <Resources.h>
#include <Config.h>
#include <Log.h>
#include <ParticleSystemFactory.h>
#include <gtc/random.hpp>


ParticleSystemWorld::ParticleSystemWorld() {
	startup();
}


ParticleSystemWorld::~ParticleSystemWorld() {
	quit();
}


void ParticleSystemWorld::quit() {
	Log::debug("begin quit");
	shutdown();
}


void ParticleSystemWorld::updateInput() {
	updateCamera();
}


void ParticleSystemWorld::updateCamera() {
	// set camera speed
	float camSpeed = 0.1f;
	if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
		camSpeed *= 4;
	}

	// move the camera forward and backward
	if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
		//scene->mainCam->position.z -= 0.1f;
		scene->mainCam->transform->translate(scene->mainCam->transform->forward().x * camSpeed, 0, scene->mainCam->transform->forward().z * camSpeed);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
		//scene->mainCam->position.z += 0.1f;
		scene->mainCam->transform->translate(-scene->mainCam->transform->forward().x * camSpeed, 0, -scene->mainCam->transform->forward().z * camSpeed);
	}

	// move the camera left and right
	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
		scene->mainCam->transform->translate(scene->mainCam->transform->left().x * camSpeed, 0, scene->mainCam->transform->left().z * camSpeed);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
		scene->mainCam->transform->translate(-scene->mainCam->transform->left().x * camSpeed, 0, -scene->mainCam->transform->left().z * camSpeed);
	}

	// move the camera up and down
	if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
		scene->mainCam->transform->translate(0, camSpeed, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
		scene->mainCam->transform->translate(0, -camSpeed, 0);
	}

	// rotate the camera left and right
	if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
		scene->mainCam->transform->rotate(0, camSpeed * 20, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		scene->mainCam->transform->rotate(0, -camSpeed * 20, 0);
	}

	// rotate the camera up and down
	if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
		scene->mainCam->transform->rotate(-camSpeed * 20, 0, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
		scene->mainCam->transform->rotate(camSpeed * 20, 0, 0);
	}
}


//============================================================================
// Overridden methods from LynxGame
//============================================================================

void ParticleSystemWorld::onClose() {
	quit();
}


void ParticleSystemWorld::onResize(int width, int height) {
	glViewport(0, 0, width, height);
	scene->mainCam->camera->aspectRatio = (float)width / (float)height;
}


void ParticleSystemWorld::onKeyReleased(KeyEvent key) {
	switch (key.code) {
	//======================================================================
	// PAUSE
	//======================================================================
	case Keyboard::Key::P:
		isPaused = !isPaused;
		printf(isPaused ? "paused\n" : "playing\n");
		break;
	//======================================================================
	// DEBUG MODE
	//======================================================================
	case Keyboard::Key::Tab:
		isDebugMode = !isDebugMode;
		// do debug stuff in here
		printf(isDebugMode ? "debug: on\n" : "debug: off\n");
		break;
	//======================================================================
	// QUIT
	//======================================================================
	case Keyboard::Key::Escape:
		quit();
		break;
	//======================================================================
	// RESET DEMO
	//======================================================================
	case Keyboard::Key::R:
		particleSystem->transform->setPosition(glm::linearRand<float>(-30, 30), glm::linearRand<float>(-30, 30), 0);
		clock.restart();
		break;
	}
}


void ParticleSystemWorld::init() {
	scene = new Scene();
	scene->mainCam->transform->setPosition(0, 0, -90);
	
	// Initialize objects.
	scene->mainCam->transform->rotate(0, 180, 0);
	
	// Seed the random number generator.
	srand(time(0));
	// Set the size of GL_POINTS for the particles.
	glPointSize(2.5f);
	// Create a particle system.
	particleSystem = ParticleSystemFactory::create("particles1", 500, true);
	particleSystem->transform->setPosition(0, 0, 0);
	scene->add(particleSystem);
}


void ParticleSystemWorld::render() {
	if (!isPaused) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene->render();
	}
}


void ParticleSystemWorld::update() {
	if (!isPaused) {
		//printf("time: %f \n", clock.getElapsedTime().asSeconds());
		updateInput();
		scene->update();
	}
}

