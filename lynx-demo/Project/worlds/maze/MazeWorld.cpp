#include "MazeWorld.h"
#include <Log.h>
#include <Collision.h>
#include <ParticleSystemFactory.h>
//using namespace glm;

const int MazeWorld::MAZE_LAYOUT[] = {
	0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0,
	0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0,
	0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0,
	0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
	0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
	0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
	0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0,
	0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
	0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0
};


MazeWorld::MazeWorld() {
	startup();
}


MazeWorld::~MazeWorld() {
	quit();
}


void MazeWorld::quit() {
	Log::debug("begin quit");
	shutdown();
}


void MazeWorld::updateInput() {
	updateCameraInput();
}


void MazeWorld::updateCameraInput() {
	//======================================================================
	// CAMERA STUFF
	//======================================================================
	float camSpeed = 0.1f;
	if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
		camSpeed *= 4;
	}

	glm::vec3 lastCamPosition = scene->mainCam->transform->position;

	// move the camera forward and backward
	if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
		scene->mainCam->transform->position += glm::vec3(scene->mainCam->transform->forward().x, 0, scene->mainCam->transform->forward().z) * camSpeed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
		scene->mainCam->transform->position -= glm::vec3(scene->mainCam->transform->forward().x, 0, scene->mainCam->transform->forward().z) * camSpeed;
	}

	// move the camera left and right
	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
		scene->mainCam->transform->position += scene->mainCam->transform->left() * camSpeed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
		scene->mainCam->transform->position -= scene->mainCam->transform->left() * camSpeed;
	}

	// move the camera up and down
	if (Keyboard::isKeyPressed(Keyboard::Key::Add)) {
		scene->mainCam->transform->position.y += camSpeed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Subtract)) {
		scene->mainCam->transform->position.y -= camSpeed;
	}

	// rotate the camera left and right
	if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
		scene->mainCam->transform->rotation.y += camSpeed * 20;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		scene->mainCam->transform->rotation.y -= camSpeed * 20;
	}

	// rotate the camera up and down
	if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
		scene->mainCam->transform->rotation.x -= camSpeed * 10;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
		scene->mainCam->transform->rotation.x += camSpeed * 10;
	}


	// Check camera colliding with walls.
	Collision camCollision;
	for (auto &i : mazeTiles) {
		if (i->collider != nullptr) {
			camCollision = Collision::checkCollision(scene->mainCam->collider, i->collider);
			// Reset to last camera position if there was a collision with the new inputs.
			if (camCollision.isCollision && i->tileType == MazeTile::TileType::WALL) scene->mainCam->transform->position = lastCamPosition;
		}
	}
}


void MazeWorld::initMaze() {
	// Create the maze based on the MAZE_LAYOUT array above.
	int mazeLayoutIndex = 0;
	int mazeSideLength = 20;
	int wallCount = 0;
	for (int z = 0; z < mazeSideLength; z++) {
		for (int x = 0; x < mazeSideLength; x++) {
			// wall
			if (MAZE_LAYOUT[mazeLayoutIndex] == 0) {
				mazeTiles.push_back(new MazeTile(MazeTile::WALL, glm::vec3(x * 2, 2, z * 2)));
				mazeTiles.back()->collider = new BoxCollider(glm::vec3(2, 2, 2), &mazeTiles.back()->transform->position);
				wallCount++;
			} // floor
			else if (MAZE_LAYOUT[mazeLayoutIndex] == 1) {
				mazeTiles.push_back(new MazeTile(MazeTile::FLOOR, glm::vec3(x * 2, 0, z * 2)));
			} // start
			else if (MAZE_LAYOUT[mazeLayoutIndex] == 8) {
				mazeTiles.push_back(new MazeTile(MazeTile::FLOOR, glm::vec3(x * 2, 0, z * 2)));
			} // end
			else if (MAZE_LAYOUT[mazeLayoutIndex] == 9) {
				mazeTiles.push_back(new MazeTile(MazeTile::FLOOR, glm::vec3(x * 2, 0, z * 2)));
			}
			scene->add(mazeTiles.back());
			mazeLayoutIndex++;
		}
	}
	printf("wall count: %u\n", wallCount);
}



//============================================================================
// Overridden methods from LynxGame
//============================================================================

void MazeWorld::onClose() {
	quit();
}


void MazeWorld::onResize(int width, int height) {
	glViewport(0, 0, width, height);
	scene->mainCam->camera->aspectRatio = (float)width / (float)height;
}



void MazeWorld::onKeyReleased(KeyEvent key) {
	switch (key.code) {
	//======================================================================
	// PAUSE
	//======================================================================
	case Keyboard::Key::P:
		isPaused = !isPaused;
		printf(isPaused ? "paused\n" : "playing\n");
		break;
	//======================================================================
	// QUIT
	//======================================================================
	case Keyboard::Key::Escape:
		quit();
		break;
	}
}


void MazeWorld::init() {
	scene = new Scene();
	Resources::loadShader("texture", "shaders/texture_vert.glsl", "shaders/texture_frag.glsl");

	initMaze();

	// Initialize objects.
	scene->mainCam->transform->setPosition(2, 2, 0);
	scene->mainCam->transform->setRotation(0, 180, 0);
	scene->mainCam->collider = new BoxCollider(glm::vec3(0.3f, 3, 0.3f), &scene->mainCam->transform->position);
	scene->add(scene->mainCam);

	sky = new GameObject("sky");
	sky->addComponent(new Graphics(sky, Resources::getMesh("models/cube_6_face.ply"), Resources::getShader("texture"), Resources::getTexture("textures/galaxy-skybox.jpg")));
	sky->transform->setScale(900, 600, 900);
	sky->transform->setRotation(0, 180, 0);
	sky->transform->setPosition(0, 0, 0);
	scene->add(sky);

	endDoor = new GameObject("end_door");
	endDoor->addComponent(new Graphics(endDoor, Resources::getMesh("models/cube_1_face.ply"), Resources::getShader("texture"), Resources::getTexture("textures/tile-blue.jpg")));
	endDoor->transform->setPosition(mazeTiles[398]->transform->position);
	endDoor->transform->position.y = 2.0f;
	endDoor->transform->position.z += 2.0f;
	endDoor->transform->setScale(2);
	endDoor->collider = new BoxCollider(glm::vec3(3), &endDoor->transform->position);
	scene->add(endDoor);

	key = new GameObject("key");
	key->addComponent(new Graphics(key, Resources::getMesh("models/torus.ply"), Resources::getShader("texture"), Resources::getTexture("textures/purpleTorus.png")));
	key->transform->setScale(0.7f);
	key->transform->setPosition(mazeTiles[170]->transform->position);
	key->transform->setRotation(0, 0, 90);
	key->collider = new SphereCollider(0.3f, &key->transform->position);
	scene->add(key);
	
	gun = new GameObject("gun");
	gun->addComponent(new Graphics(gun, Resources::getMesh("models/gun.ply"), Resources::getShader("texture"), Resources::getTexture("textures/gun-1.png")));
	gun->transform->setScale(0.1f);
	gun->transform->setPosition(mazeTiles[61]->transform->position + glm::vec3(0, collectableHeightOffset, 0));
	gun->collider = new SphereCollider(0.2f, &gun->transform->position);
	// Add mag to gun.
	GameObject *mag = new GameObject("mag");
	mag->addComponent(new Graphics(mag, Resources::getMesh("models/mag.ply"), Resources::getShader("texture"), Resources::getTexture("textures/mag-1.png")));
	gun->transform->addChild(mag->transform);
	scene->add(gun);
}


void MazeWorld::render() {
	if (!isPaused) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene->render();
	}
}


void MazeWorld::update() {
	if (!isPaused) {
		// If gun hasn't been picked up, check collision.
		phase += frequency;
		if (!hasPickedUpGun) {
			gun->transform->rotation += glm::vec3(0, 0.2f, 0);
			gun->transform->position.y = sin(phase) * amp + collectableHeightOffset;
			Collision c = Collision::checkCollision(scene->mainCam->collider, gun->collider);
			if (c.isCollision) {
				hasPickedUpGun = true;
				gun->transform->position = glm::vec3(-0.2f, -0.1f, 0.2f);
				gun->transform->rotation = glm::vec3(0, 90, 0);
				gun->transform->scale = glm::vec3(0.03f);
				scene->mainCam->transform->addChild(gun->transform);
			}
		}
		if (!hasPickedUpKey) {
			key->transform->rotation += glm::vec3(0, 0.2f, 0);
			key->transform->position.y = sin(phase) * amp + collectableHeightOffset;
			Collision c = Collision::checkCollision(scene->mainCam->collider, key->collider);
			if (c.isCollision) {
				hasPickedUpKey = true;
				key->transform->position = glm::vec3(0.2f, -0.1f, 0.2f);
				key->transform->scale = glm::vec3(0.1f);
				key->transform->rotation = glm::vec3(0, 0, 90);
				scene->mainCam->transform->addChild(key->transform);
			}
		}
		if (hasPickedUpKey && !hasOpenedDoor) {
			Collision c = Collision::checkCollision(scene->mainCam->collider, endDoor->collider);
			if (c.isCollision) {
				hasOpenedDoor = true;
				key->transform->position.z -= 5.0f; // hide the key behind the player, don't need it anymore

				// Add particle system.
				clock.restart();
				// Set the size of GL_POINTS for the particles.
				glPointSize(5.5f);
				GameObject* particleSystem = ParticleSystemFactory::create("particleSystem", 20000, true);
				particleSystem->transform->setPosition(endDoor->transform->position);
				scene->add(particleSystem);
			}
		}
		if (hasOpenedDoor && endDoor->transform->position.y > -3.0f) {
			endDoor->transform->position.y -= 0.02f;
		}

		updateInput();
		scene->update();
	}
}
