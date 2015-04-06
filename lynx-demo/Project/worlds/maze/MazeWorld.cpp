//#include "MazeWorld.h"
//using namespace glm;
//
//const int Game::MAZE_LAYOUT[] = {
//	0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
//	0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
//	0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0,
//	0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0,
//	0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
//	0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0,
//	0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0,
//	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0,
//	0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
//	0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0,
//	0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
//	0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
//	0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
//	0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0,
//	0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
//	0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0,
//	0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
//	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0
//};
//
//
//Game::Game() {
//	setup(1280, 720, "The Maze", "THE_LOG");
//	// Check OpenGL error.
//	/*GLenum err;
//	while ((err = glGetError()) != GL_NO_ERROR) {
//		std::cout << "OpenGL error: " << err << std::endl;
//	}*/
//}
//
//
//Game::~Game() {
//	quit();
//}
//
//
//void Game::quit() {
//	Log::debug("begin quit");
//	shutdown();
//}
//
//
//void Game::updateInput() {
//	updateCameraInput();
//	//======================================================================
//	// QUICK TESTING
//	//======================================================================
//	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad8)) {
//	}
//	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad5)) {
//	}
//	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad6)) {
//	}
//	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad4)) {
//	}
//	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad9)) {
//	}
//	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad3)) {
//	}
//}
//
//
//void Game::updateCameraInput() {
//	//======================================================================
//	// CAMERA STUFF
//	//======================================================================
//	float camSpeed = 0.1f;
//	if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
//		camSpeed *= 4;
//	}
//
//	vec3 lastCamPosition = scene->mainCam->position;
//
//	// move the camera forward and backward
//	if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
//		scene->mainCam->position += glm::vec3(scene->mainCam->forward().x, 0, scene->mainCam->forward().z) * camSpeed;
//	}
//	else if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
//		scene->mainCam->position -= glm::vec3(scene->mainCam->forward().x, 0, scene->mainCam->forward().z) * camSpeed;
//	}
//
//	// move the camera left and right
//	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
//		scene->mainCam->position += scene->mainCam->left() * camSpeed;
//	}
//	else if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
//		scene->mainCam->position -= scene->mainCam->left() * camSpeed;
//	}
//
//	// move the camera up and down
//	if (Keyboard::isKeyPressed(Keyboard::Key::Add)) {
//		scene->mainCam->position.y += camSpeed;
//	}
//	else if (Keyboard::isKeyPressed(Keyboard::Key::Subtract)) {
//		scene->mainCam->position.y -= camSpeed;
//	}
//
//	// rotate the camera left and right
//	if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
//		scene->mainCam->rotation.y += camSpeed * 20;
//	}
//	else if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
//		scene->mainCam->rotation.y -= camSpeed * 20;
//	}
//
//	// rotate the camera up and down
//	if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
//		scene->mainCam->rotation.x -= camSpeed * 10;
//	}
//	else if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
//		scene->mainCam->rotation.x += camSpeed * 10;
//	}
//
//
//	// Check camera colliding with walls.
//	Collision camCollision;
//	for (auto &i : mazeTiles) {
//		if (i->collider != nullptr) {
//			camCollision = Collision::checkCollision(scene->mainCam->collider, i->collider);
//			// Reset to last camera position if there was a collision with the new inputs.
//			if (camCollision.isCollision && i->tileType == MazeTile::TileType::WALL) scene->mainCam->position = lastCamPosition;
//		}
//	}
//}
//
//
//void Game::initMaze() {
//	// Create the maze based on the MAZE_LAYOUT array above.
//	int mazeLayoutIndex = 0;
//	int mazeSideLength = 20;
//	int wallCount = 0;
//	for (int z = 0; z < mazeSideLength; z++) {
//		for (int x = 0; x < mazeSideLength; x++) {
//			// wall
//			if (MAZE_LAYOUT[mazeLayoutIndex] == 0) {
//				mazeTiles.push_back(new MazeTile(MazeTile::WALL, vec3(x * 2, 2, z * 2)));
//				mazeTiles.back()->collider = new BoxCollider(vec3(2,2,2), &mazeTiles.back()->position);
//				wallCount++;
//			} // floor
//			else if (MAZE_LAYOUT[mazeLayoutIndex] == 1) {
//				mazeTiles.push_back(new MazeTile(MazeTile::FLOOR, vec3(x * 2, 0, z * 2)));
//			} // start
//			else if (MAZE_LAYOUT[mazeLayoutIndex] == 8) {
//				mazeTiles.push_back(new MazeTile(MazeTile::FLOOR, vec3(x * 2, 0, z * 2)));
//			} // end
//			else if (MAZE_LAYOUT[mazeLayoutIndex] == 9) {
//				mazeTiles.push_back(new MazeTile(MazeTile::FLOOR, vec3(x * 2, 0, z * 2)));
//			}
//			scene->add(mazeTiles.back());
//			mazeLayoutIndex++;
//		}
//	}
//	printf("wall count: %u\n", wallCount);
//}
//
//
//
////============================================================================
//// Overridden methods from LynxGame
////============================================================================
//
//void Game::onClose() {
//	quit();
//}
//
//
//void Game::onResize(int width, int height) {
//	glViewport(0, 0, width, height);
//	scene->mainCam->aspectRatio = (float)width / (float)height;
//}
//
//
//void Game::onKeyPressed(KeyEvent key) {}
//
//
//void Game::onKeyReleased(KeyEvent key) {
//	switch (key.code) {
//	//======================================================================
//	// PAUSE
//	//======================================================================
//	case Keyboard::Key::P:
//		isPaused = !isPaused;
//		printf(isPaused ? "paused\n" : "playing\n");
//		break;
//	//======================================================================
//	// DEBUG MODE
//	//======================================================================
//	case Keyboard::Key::Tab:
//		isDebugMode = !isDebugMode;
//		// Make colliders render.
//		for (auto &i : scene->sceneObjects) {
//			if (i->collider != nullptr) i->collider->isRender = isDebugMode;
//		}
//		if (scene->mainCam->collider != nullptr) scene->mainCam->collider->isRender = isDebugMode;
//		printf(isDebugMode ? "debug: on\n" : "debug: off\n");
//		break;
//	//======================================================================
//	// QUIT
//	//======================================================================
//	case Keyboard::Key::Escape:
//		quit();
//		break;
//	}
//
//	//Spawn new cubes.
//	/*if (glfwGetKey(window, GLFW_KEY_SPACE) && !isSpaceKeyDown) {
//	isSpaceKeyDown = true;
//	GameObject *newCube = new GameObject(GameObject::PRIMITIVE_CUBE, shaderManager->getShader("texture"), circleTexture);
//	newCube->position = scene->mainCam->position + glm::vec3(0, 0, -1);
//	newCube->scale = glm::vec3(0.03f);
//	scene->add(newCube);
//	}*/
//	/*if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
//	isSpaceKeyDown = false;
//	}*/
//}
//
//
//void  Game::onMouseButtonPressed(MouseButtonEvent mouse) {}
//
//
//void  Game::onMouseButtonReleased(MouseButtonEvent mouse) {}
//
//
//void Game::init() {
//	FreeImage_Initialise(true);
//	scene = new Scene(glm::vec4(0, 0, 0, 1), (float)1280/(float)720);
//	ShaderManager::getInstance()->loadShader("texture", "shaders/texture_vert.glsl", "shaders/texture_frag.glsl");
//	//ShaderManager::getInstance()->loadShader("normal", "shaders/normal_vert.glsl", "shaders/normal_frag.glsl");
//
//	initMaze();
//
//	// Initialize objects.
//	monkey = new GameObject(MeshManager::getInstance()->get("models/monkey.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/monkey.png"));
//	monkey->position = vec3(0, 10, 0);
//	sky = new GameObject(MeshManager::getInstance()->get("models/cube_6_face.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/skybox2.jpg"));
//	sky->scale = vec3(9000, 6000, 9000);
//	sky->rotation = vec3(180, 0, 0);
//	sky->position = vec3(0, 1400, 0);
//	endDoor = new GameObject(GameObject::PRIMITIVE_QUAD, ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/end_door.jpg"));
//	endDoor->position = mazeTiles[398]->position;
//	endDoor->position.y = 2.0f;
//	endDoor->collider = new BoxCollider(vec3(1), &endDoor->position);
//	key = new GameObject(MeshManager::getInstance()->get("models/torus.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/key.png"));
//	key->scale = vec3(0.7f);
//	key->position = mazeTiles[170]->position;
//	key->rotation = vec3(0, 0, 90);
//	key->collider = new SphereCollider(0.3f, &key->position);
//	gun = new GameObject(MeshManager::getInstance()->get("models/gun.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/gun-1.png"));
//	// Add mag to gun.
//	gun->addChild(new GameObject(MeshManager::getInstance()->get("models/mag.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/mag-1.png")));
//	gun->scale = vec3(0.1f);
//	gun->position = mazeTiles[61]->position + vec3(0, collectableHeightOffset, 0);
//	gun->rotation = vec3(0, 0, 0);
//	gun->collider = new SphereCollider(0.2f, &gun->position);
//	scene->mainCam->collider = new BoxCollider(vec3(0.3f, 3, 0.3f), &scene->mainCam->position);
//
//	//scene->mainCam->addChild(cube1);
//	// Add objects to the scene.
//	//scene->add(monkey);
//	scene->add(gun);
//	scene->add(sky);
//	scene->add(key);
//	scene->add(endDoor);
//	scene->add(scene->mainCam);
//}
//
//
//void Game::render() {
//	if (!isPaused) {
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		scene->render();
//	}
//}
//
//
//void Game::update() {
//	if (!isPaused) {
//		// If gun hasn't been picked up, check collision.
//		phase += frequency;
//		if (!hasPickedUpGun) {
//			gun->rotation += vec3(0, 0.2f, 0);
//			gun->position.y = sin(phase) * amp + collectableHeightOffset;
//			Collision c = Collision::checkCollision(scene->mainCam->collider, gun->collider);
//			if (c.isCollision) {
//				hasPickedUpGun = true;
//				gun->position = vec3(0.2f, -0.1f,-0.2f);
//				gun->rotation = vec3(0, -90, 0);
//				gun->scale = vec3(0.03f);
//				scene->mainCam->addChild(gun);
//			}
//		}
//		if (!hasPickedUpKey) {
//			key->rotation += vec3(0, 0.2f, 0);
//			key->position.y = sin(phase) * amp + collectableHeightOffset;
//			Collision c = Collision::checkCollision(scene->mainCam->collider, key->collider);
//			if (c.isCollision) {
//				hasPickedUpKey = true;
//				key->position = vec3(-0.2f, -0.1f, -0.2f);
//				key->scale = vec3(0.1f);
//				key->rotation = vec3(0, 0, 90);
//				scene->mainCam->addChild(key);
//			}
//		}
//		if (hasPickedUpKey && !hasOpenedDoor) {
//			Collision c = Collision::checkCollision(scene->mainCam->collider, endDoor->collider);
//			if (c.isCollision) {
//				hasOpenedDoor = true;
//				key->position.z += 5.0f; // hide the key from, don't need it anymore
//			}
//		}
//		if (hasOpenedDoor && endDoor->position.y > -3.0f) {
//			endDoor->position.y -= 0.02f;
//		}
//
//		updateInput();
//		scene->update();
//	}
//}
