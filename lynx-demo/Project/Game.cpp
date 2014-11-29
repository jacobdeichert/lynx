#include "Game.h"


Game::Game() {
	setup(1280, 720, "OpenGL Demo");
	// Check OpenGL error.
	/*GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << err << std::endl;
	}*/




}



Game::~Game() {}


void Game::onClose() {
	printf("onClose\n");
}


void Game::onKeyDown(KeyCode key) {
	printf("onKeyDown\n");
	
}


void Game::onKeyUp(KeyCode key) {
	printf("onKeyUp\n");

}


void Game::onResize(int width, int height) {
	printf("onResize\n");
	glViewport(0, 0, width, height);
	scene->mainCam->aspectRatio = (float)width / (float)height;
}


void Game::init() {
	printVersionInfo();
	FreeImage_Initialise(true);
	scene = new Scene(glm::vec4(0, 0, 0, 1), (float)1280/(float)720);


	ShaderManager::getInstance()->loadShader("texture", "shaders/texture_vert.glsl", "shaders/texture_frag.glsl");
	ShaderManager::getInstance()->loadShader("normal", "shaders/normal_vert.glsl", "shaders/normal_frag.glsl");
	//shaderManager->loadShader("simple", "shaders/SimpleVertexShader.glsl", "shaders/SimpleFragmentShader.glsl");
	//shaderManager->loadShader("ali", "shaders/AliVertexShader.glsl", "shaders/AliFragmentShader.glsl");



	// Initialize objects.
	triangle1 = new GameObject(GameObject::PRIMITIVE_TRIANGLE, ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/tron.png"));
	square1 = new GameObject(GameObject::PRIMITIVE_QUAD, ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/jd.png"));
	square2 = new GameObject(GameObject::PRIMITIVE_QUAD, ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/jd.png"));
	cube1 = new GameObject(MeshManager::getInstance()->get("models/cube_1_face.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/tron.png"));
	cube2 = new GameObject(MeshManager::getInstance()->get("models/cube_6_face.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/die.png"));
	cube3 = new GameObject(MeshManager::getInstance()->get("models/cube_1_face.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/circle.png"));
	sphere1 = new GameObject(MeshManager::getInstance()->get("models/sphere.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/purpleBall.png"));
	sphere2 = new GameObject(MeshManager::getInstance()->get("models/sphere.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/tron.png"));
	monkey = new GameObject(MeshManager::getInstance()->get("models/monkey.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/tron.png"));
	ground = new GameObject(GameObject::PRIMITIVE_QUAD, ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/metal.jpg"));
	gun = new GameObject(MeshManager::getInstance()->get("models/gun.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/gun-1.png"));
	
	

	triangle1->position = glm::vec3(0.0f, -0.2f, 0.7f);
	triangle1->scale = glm::vec3(8);
	triangle1->rotation = glm::vec3(0, 90, 0);

	square1->position = glm::vec3(-0.9f, 0, -1.6f);
	square1->rotation = glm::vec3(0, 0, 0);
	square1->scale = glm::vec3(0.4f);

	square2->position = glm::vec3(0.8f, 0.1f, -0.01f);
	square2->scale = glm::vec3(0.4f);

	cube1->position = glm::vec3(0.5f, -0.3f, -0.95f);
	cube1->scale = glm::vec3(0.06f, 0.3f, 0.06f);
	cube1->rotation = glm::vec3(90, 0, 0);

	cube2->position = glm::vec3(5.75f, 0.4f, -0.3f);
	cube2->scale = glm::vec3(0.4f);
	cube2->collider = new BoxCollider(glm::vec3(0.5f), &cube2->position);

	cube3->position = glm::vec3(5.75f, -0.4f, -0.3f);
	cube3->scale = glm::vec3(0.5f);
	cube3->collider = new BoxCollider(glm::vec3(0.5f), &cube3->position);

	sphere1->position = glm::vec3(5.5f, -0.4f, -1.3f);
	sphere1->collider = new SphereCollider(0.5f, &sphere1->position);

	sphere2->position = glm::vec3(7.0f, -0.4f, -1.3f);
	sphere2->collider = new SphereCollider(0.75f, &sphere2->position);
	sphere2->scale = glm::vec3(1.0f);

	monkey->position = glm::vec3(0, 20.0f, 0);
	monkey->rotation = glm::vec3(-90.0f, 0, 0);

	ground->position = glm::vec3(0, -8.0f, 0);
	ground->rotation = glm::vec3(-90, 0, 0);
	ground->scale = glm::vec3(70);

	gun->position = glm::vec3(0, 20, 0);



	//square1->addChild(cube1);
	square2->addChild(triangle1);
	//square1->addChild(scene->mainCam);
	scene->mainCam->addChild(cube1);

	// add mag to gun
	gun->addChild(new GameObject(MeshManager::getInstance()->get("models/mag.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/mag-1.png")));


	// Add objects to the scene.
	//scene->add(triangle1);
	scene->add(square1);
	scene->add(square2);
	scene->add(cube2);
	scene->add(cube3);
	scene->add(sphere1);
	scene->add(sphere2);
	scene->add(monkey);
	scene->add(ground);
	scene->add(gun);
	scene->add(scene->mainCam);
}



void Game::render() {
	if (!isPaused) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene->render();
	}
}



void Game::update() {
	updateInput();
	if (!isPaused) {
		//Collision col = Collision::checkCollision(cube2->collider, sphere2->collider);
		//if (col.isCollision) printf("cube2 > sphere2        %f\n", (float)glfwGetTime());
		//col = Collision::checkCollision(sphere1->collider, sphere2->collider);
		//if (col.isCollision) printf("sphere1 > sphere2        %f\n", (float)glfwGetTime());
		//col = Collision::checkCollision(cube3->collider, cube2->collider);
		//if (col.isCollision) printf("cube3 > cube2        %f\n", (float)glfwGetTime());
		// Parametric Equation (spiral)
		//sphere1->position.x = glfwGetTime() * cos(glfwGetTime());
		//sphere1->position.y = glfwGetTime() * sin(glfwGetTime());
		// Parametric Equation (circle)
		//monkey->position.x = cos((float)glfwGetTime());
		//monkey->position.y = sin((float)glfwGetTime()) + 10.0f;
		scene->update();
	}
}



void Game::updateInput() {
	//======================================================================
	// TESTING
	//======================================================================
	// Keys for quick testing of things.
	//if (glfwGetKey(window, GLFW_KEY_KP_8)) {
	//	sphere2->position += sphere2->forward() * 0.01f;
	//	//cube2->position += cube2->forward() * 0.01f;
	//}
	//if (glfwGetKey(window, GLFW_KEY_KP_5)) {
	//	sphere2->position -= sphere2->forward() * 0.01f;
	//	//cube2->position -= cube2->forward() * 0.01f;
	//}
	//if (glfwGetKey(window, GLFW_KEY_KP_4)) {
	//	sphere2->position -= sphere2->right() * 0.01f;
	//	//cube2->position -= cube2->right() * 0.01f;
	//	//square2->scale += glm::vec3(0.1f);
	//}
	//if (glfwGetKey(window, GLFW_KEY_KP_6)) {
	//	sphere2->position += sphere2->right() * 0.01f;
	//	//cube2->position += cube2->right() * 0.01f;
	//	//square2->scale += glm::vec3(0.1f);
	//}
	//if (glfwGetKey(window, GLFW_KEY_KP_9)) {
	//	sphere2->position += glm::vec3(0, 0.01f, 0);
	//	//cube2->position += glm::vec3(0, 0.01f, 0);
	//	//square2->scale += glm::vec3(0.1f);
	//}
	//if (glfwGetKey(window, GLFW_KEY_KP_3)) {
	//	sphere2->position -= glm::vec3(0, 0.01f, 0);
	//	//cube2->position -= glm::vec3(0, 0.01f, 0);
	//	//square2->scale += glm::vec3(0.1f);
	//}



	//// Spawn new cubes.
	///*if (glfwGetKey(window, GLFW_KEY_SPACE) && !isSpaceKeyDown) {
	//isSpaceKeyDown = true;
	//GameObject *newCube = new GameObject(GameObject::PRIMITIVE_CUBE, shaderManager->getShader("texture"), circleTexture);
	//newCube->position = scene->mainCam->position + glm::vec3(0, 0, -1);
	//newCube->scale = glm::vec3(0.03f);
	//scene->add(newCube);
	//}*/
	///*if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
	//	isSpaceKeyDown = false;
	//}*/





	////======================================================================
	//// ROTATE STUFF
	////======================================================================

	//// the plus/equals key
	//float rotateDir = 0;
	//if (glfwGetKey(window, GLFW_KEY_EQUAL)) {
	//	rotateDir = 3.0f;
	//} // the minus/dash/underscore key
	//else if (glfwGetKey(window, GLFW_KEY_MINUS)) {
	//	rotateDir = -3.0f;
	//}

	//// rotate X
	//if (glfwGetKey(window, GLFW_KEY_X)) {
	//	square1->rotation.x += rotateDir;
	//	square2->rotation.x += rotateDir;
	//	cube2->rotation.x += rotateDir;
	//	sphere1->rotation.x += rotateDir;
	//}
	//// rotate Y
	//if (glfwGetKey(window, GLFW_KEY_Y)) {
	//	square1->rotation.y += rotateDir;
	//	square2->rotation.y += rotateDir;
	//	cube2->rotation.y += rotateDir;
	//	sphere1->rotation.y += rotateDir;
	//}
	//// rotate Z
	//if (glfwGetKey(window, GLFW_KEY_Z)) {
	//	square1->rotation.z += rotateDir;
	//	square2->rotation.z += rotateDir;
	//	cube2->rotation.z += rotateDir;
	//	sphere1->rotation.z += rotateDir;
	//}



	////======================================================================
	//// PAUSE MODE
	////======================================================================
	//if (glfwGetKey(window, GLFW_KEY_P) && !isPKeyDown) {
	//	isPaused = !isPaused;
	//	isPKeyDown = true;
	//}
	//if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE) {
	//	isPKeyDown = false;
	//}



	////======================================================================
	//// DEBUG MODE
	////======================================================================
	//if (glfwGetKey(window, GLFW_KEY_TAB) && !isTabKeyDown) {
	//	isDebugMode = !isDebugMode;
	//	isTabKeyDown = true;
	//	// Make colliders render.
	//	for (auto &i : scene->sceneObjects) {
	//		if (i->collider != nullptr) i->collider->isRender = isDebugMode;
	//	}
	//}
	//if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) {
	//	isTabKeyDown = false;
	//}


	////======================================================================
	//// CAMERA STUFF
	////======================================================================
	//float camSpeed = 0.1f;
	//if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
	//	camSpeed *= 4;
	//}

	//// move the camera forward and backward
	//if (glfwGetKey(window, GLFW_KEY_W)) {
	//	//scene->mainCam->position.z -= 0.1f;
	//	scene->mainCam->position += glm::vec3(scene->mainCam->forward().x, 0, scene->mainCam->forward().z) * camSpeed;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_S)) {
	//	//scene->mainCam->position.z += 0.1f;
	//	scene->mainCam->position -= glm::vec3(scene->mainCam->forward().x, 0, scene->mainCam->forward().z) * camSpeed;
	//}

	//// move the camera left and right
	//if (glfwGetKey(window, GLFW_KEY_A)) {
	//	scene->mainCam->position -= scene->mainCam->right() * camSpeed;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_D)) {
	//	scene->mainCam->position += scene->mainCam->right() * camSpeed;
	//}

	//// move the camera up and down
	//if (glfwGetKey(window, GLFW_KEY_KP_ADD)) {
	//	scene->mainCam->position.y += camSpeed;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT)) {
	//	scene->mainCam->position.y -= camSpeed;
	//}

	//// rotate the camera left and right
	//if (glfwGetKey(window, GLFW_KEY_LEFT)) {
	//	scene->mainCam->rotation.y += camSpeed * 20;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
	//	scene->mainCam->rotation.y -= camSpeed * 20;
	//}

	//// rotate the camera up and down
	//if (glfwGetKey(window, GLFW_KEY_UP)) {
	//	scene->mainCam->rotation.x += camSpeed * 10;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_DOWN)) {
	//	scene->mainCam->rotation.x -= camSpeed * 10;
	//}
}




void Game::printVersionInfo() {
	printf("============================================================\n");
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("OpenGL Shading Language Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("============================================================\n");
}

