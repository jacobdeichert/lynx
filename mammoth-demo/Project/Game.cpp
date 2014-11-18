#include "Game.h"


Game::Game() {
	createWindow();
	init();
	// Check OpenGL error.
	/*GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << err << std::endl;
	}*/
	start();
}



Game::~Game() {}



void Game::init() {
	printVersionInfo();
	FreeImage_Initialise(true);
	scene = new Scene();
	//shaderManager->loadShader("simple", "shaders/SimpleVertexShader.glsl", "shaders/SimpleFragmentShader.glsl");
	shaderManager->loadShader("texture", "shaders/TextureVertexShader.glsl", "shaders/TextureFragmentShader.glsl");
	shaderManager->loadShader("textureCopy", "shaders/TextureVertexShaderCopy.glsl", "shaders/TextureFragmentShaderCopy.glsl");
	//shaderManager->loadShader("ali", "shaders/AliVertexShader.glsl", "shaders/AliFragmentShader.glsl");

	meshManager = MeshManager::getInstance();
	meshManager->load("cube", "models/cube.ply");
	meshManager->load("cube6", "models/cube6Face.ply");
	meshManager->load("sphere", "models/sphere.ply");
	meshManager->load("monkey", "models/monkey.ply");

	textureManager->load("circle", "textures/circle.png");
	textureManager->load("jd", "textures/jd.png");
	textureManager->load("tron", "textures/tron.png");
	textureManager->load("die", "textures/die.png");
	textureManager->load("purpleBall", "textures/purpleBall.png");
	Texture *circleTexture = textureManager->get("circle");
	Texture *jdTexture = textureManager->get("jd");
	Texture *tronTexture = textureManager->get("tron");
	Texture *dieTexture = textureManager->get("die");
	Texture *purpleBallTexture = textureManager->get("purpleBall");





	// Set the clear color.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Initialize objects.
	triangle1 = new GameObject(GameObject::PRIMITIVE_TRIANGLE, shaderManager->getShader("texture"), tronTexture);
	square1 = new GameObject(GameObject::PRIMITIVE_QUAD, shaderManager->getShader("texture"), jdTexture);
	square2 = new GameObject(GameObject::PRIMITIVE_QUAD, shaderManager->getShader("texture"), jdTexture);
	cube1 = new GameObject(meshManager->get("cube"), GL_TRIANGLES, shaderManager->getShader("texture"), tronTexture);
	cube2 = new GameObject(meshManager->get("cube"), GL_TRIANGLES, shaderManager->getShader("texture"), tronTexture);
	sphere = new GameObject(meshManager->get("sphere"), GL_TRIANGLES, shaderManager->getShader("texture"), purpleBallTexture);
	monkey = new GameObject(meshManager->get("monkey"), GL_TRIANGLES, shaderManager->getShader("texture"), tronTexture);
	ground = new GameObject(GameObject::PRIMITIVE_QUAD, shaderManager->getShader("texture"), jdTexture);
	triangle1->position = glm::vec3(0.0f, -0.2f, 0.7f);
	triangle1->scale = glm::vec3(8);
	triangle1->rotation = glm::vec3(0, 90, 0);
	square1->position = glm::vec3(-0.9f, 0.1f, -1.6f);
	square1->scale = glm::vec3(0.4f);
	square2->position = glm::vec3(0.8f, 0.1f, -0.01f);
	square2->scale = glm::vec3(0.4f);
	cube1->position = glm::vec3(0.5f, -0.3f, -0.95f);
	cube1->scale = glm::vec3(0.06f, 0.3f, 0.06f);
	cube1->rotation = glm::vec3(90, 0, 0);
	cube2->position = glm::vec3(0, 2.0f, -1.0f);
	cube2->scale = glm::vec3(0.4f);
	sphere->position = glm::vec3(5.5f, -0.4f, -1.3f);
	monkey->position = glm::vec3(0, 20.0f, 0);
	monkey->rotation = glm::vec3(-90.0f, 0, 0);

	ground->position = glm::vec3(0, -10.0f, 0);
	ground->rotation = glm::vec3(-90, 0, 0);
	ground->scale = glm::vec3(100);


	//square1->addChild(cube1);
	square2->addChild(triangle1);
	//square1->addChild(scene->mainCam);
	scene->mainCam->addChild(cube1);


	// Add objects to the scene.
	//scene->add(triangle1);
	scene->add(square1);
	scene->add(square2);
	scene->add(cube2);
	scene->add(sphere);
	scene->add(monkey);
	scene->add(ground);
	scene->add(scene->mainCam);
}



void Game::printVersionInfo() {
	printf("============================================================\n");
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("OpenGL Shading Language Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("============================================================\n\n");
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
		// Parametric Equation (spiral)
		//sphere->position.x = glfwGetTime() * cos(glfwGetTime());
		//sphere->position.y = glfwGetTime() * sin(glfwGetTime());
		scene->update();
	}
}



void Game::updateInput() {
	float rotateDir = 0;


	// Keys for quick testing of things.
	if (glfwGetKey(window, GLFW_KEY_KP_8)) {
		square2->position += square2->forward() * 0.06f;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_5)) {
		square2->position -= square2->forward() * 0.06f;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_4)) {
		square2->position -= square2->right() * 0.06f;
		//square2->scale += glm::vec3(0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_KP_6)) {
		square2->position += square2->right() * 0.06f;
		//square2->scale += glm::vec3(0.1f);
	}



	// Spawn new cubes.
	/*if (glfwGetKey(window, GLFW_KEY_SPACE) && !isSpaceKeyDown) {
	isSpaceKeyDown = true;
	GameObject *newCube = new GameObject(GameObject::PRIMITIVE_CUBE, shaderManager->getShader("texture"), circleTexture);
	newCube->position = scene->mainCam->position + glm::vec3(0, 0, -1);
	newCube->scale = glm::vec3(0.03f);
	scene->add(newCube);
	}*/

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		isSpaceKeyDown = false;
	}




	// the plus/equals key
	if (glfwGetKey(window, GLFW_KEY_EQUAL)) {
		rotateDir = 3.0f;
	} // the minus/dash/underscore key
	else if (glfwGetKey(window, GLFW_KEY_MINUS)) {
		rotateDir = -3.0f;
	}


	// rotate X
	if (glfwGetKey(window, GLFW_KEY_X)) {
		square1->rotation.x += rotateDir;
		square2->rotation.x += rotateDir;
		cube2->rotation.x += rotateDir;
		sphere->rotation.x += rotateDir;
	}
	// rotate Y
	if (glfwGetKey(window, GLFW_KEY_Y)) {
		square1->rotation.y += rotateDir;
		square2->rotation.y += rotateDir;
		cube2->rotation.y += rotateDir;
		sphere->rotation.y += rotateDir;
	}
	// rotate Z
	if (glfwGetKey(window, GLFW_KEY_Z)) {
		square1->rotation.z += rotateDir;
		square2->rotation.z += rotateDir;
		cube2->rotation.z += rotateDir;
		sphere->rotation.z += rotateDir;
	}



	if (glfwGetKey(window, GLFW_KEY_P) && !isPKeyDown) {
		isPaused = !isPaused;
		isPKeyDown = true;
		printf("hit\n");
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE) {
		isPKeyDown = false;
	}


	// move the camera forward and backward
	if (glfwGetKey(window, GLFW_KEY_W)) {
		//scene->mainCam->position.z -= 0.1f;
		scene->mainCam->position += scene->mainCam->forward() * 0.07f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S)) {
		//scene->mainCam->position.z += 0.1f;
		scene->mainCam->position -= scene->mainCam->forward() * 0.07f;
	}

	// move the camera left and right
	if (glfwGetKey(window, GLFW_KEY_A)) {
		scene->mainCam->position -= scene->mainCam->right() * 0.07f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D)) {
		scene->mainCam->position += scene->mainCam->right() * 0.07f;
	}

	// move the camera up and down
	if (glfwGetKey(window, GLFW_KEY_KP_ADD)) {
		scene->mainCam->position.y += 0.2f;
	}
	else if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT)) {
		scene->mainCam->position.y -= 0.2f;
	}

	// rotate the camera left and right
	if (glfwGetKey(window, GLFW_KEY_LEFT)) {
		scene->mainCam->rotation.y += 2.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
		scene->mainCam->rotation.y -= 2.0f;
	}

	// rotate the camera up and down
	if (glfwGetKey(window, GLFW_KEY_UP)) {
		scene->mainCam->rotation.x += 2.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN)) {
		scene->mainCam->rotation.x -= 2.0f;
	}
}



