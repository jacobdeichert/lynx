#include "Game.h"


Game::Game() {
	setup(1280, 720, "OpenGL Demo", "THE_LOG");
	// Check OpenGL error.
	/*GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << err << std::endl;
	}*/
}

Game::~Game() {
	quit();
}

void Game::quit() {
	Log::debug("begin quit");
	shutdown();
}

void Game::updateInput() {
	//======================================================================
	// QUICK TESTING
	//======================================================================
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad8)) {
		sphere2->position += sphere2->forward() * 0.01f;
		//cube2->position += cube2->forward() * 0.01f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad5)) {
		sphere2->position -= sphere2->forward() * 0.01f;
		//cube2->position -= cube2->forward() * 0.01f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad6)) {
		sphere2->position -= sphere2->left() * 0.01f;
		//cube2->position -= cube2->right() * 0.01f;
		//square2->scale += glm::vec3(0.1f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad4)) {
		sphere2->position += sphere2->left() * 0.01f;
		//cube2->position += cube2->right() * 0.01f;
		//square2->scale += glm::vec3(0.1f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad9)) {
		sphere2->position += glm::vec3(0, 0.01f, 0);
		//cube2->position += glm::vec3(0, 0.01f, 0);
		//square2->scale += glm::vec3(0.1f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad3)) {
		sphere2->position -= glm::vec3(0, 0.01f, 0);
		//cube2->position -= glm::vec3(0, 0.01f, 0);
		//square2->scale += glm::vec3(0.1f);
	}


	//======================================================================
	// ROTATE STUFF
	//======================================================================
	float rotateDir = 0;
	if (Keyboard::isKeyPressed(Keyboard::Key::Equal)) {
		rotateDir = 3.0f;
	} // the minus/dash/underscore key
	else if (Keyboard::isKeyPressed(Keyboard::Key::Dash)) {
		rotateDir = -3.0f;
	}

	// rotate X
	if (Keyboard::isKeyPressed(Keyboard::Key::X)) {
		square1->rotation.x += rotateDir;
		square2->rotation.x += rotateDir;
		cube2->rotation.x += rotateDir;
		sphere1->rotation.x += rotateDir;
	}
	// rotate Y
	if (Keyboard::isKeyPressed(Keyboard::Key::Y)) {
		square1->rotation.y += rotateDir;
		square2->rotation.y += rotateDir;
		cube2->rotation.y += rotateDir;
		sphere1->rotation.y += rotateDir;
	}
	// rotate Z
	if (Keyboard::isKeyPressed(Keyboard::Key::Z)) {
		square1->rotation.z += rotateDir;
		square2->rotation.z += rotateDir;
		cube2->rotation.z += rotateDir;
		sphere1->rotation.z += rotateDir;
	}


	//======================================================================
	// CAMERA STUFF
	//======================================================================
	float camSpeed = 0.1f;
	if (Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
		camSpeed *= 4;
	}

	// move the camera forward and backward
	if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
		//scene->mainCam->position.z -= 0.1f;
		scene->mainCam->position += glm::vec3(scene->mainCam->forward().x, 0, scene->mainCam->forward().z) * camSpeed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
		//scene->mainCam->position.z += 0.1f;
		scene->mainCam->position -= glm::vec3(scene->mainCam->forward().x, 0, scene->mainCam->forward().z) * camSpeed;
	}

	// move the camera left and right
	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
		scene->mainCam->position += scene->mainCam->left() * camSpeed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
		scene->mainCam->position -= scene->mainCam->left() * camSpeed;
	}

	// move the camera up and down
	if (Keyboard::isKeyPressed(Keyboard::Key::Add)) {
		scene->mainCam->position.y += camSpeed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Subtract)) {
		scene->mainCam->position.y -= camSpeed;
	}

	// rotate the camera left and right
	if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
		scene->mainCam->rotation.y += camSpeed * 20;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		scene->mainCam->rotation.y -= camSpeed * 20;
	}

	// rotate the camera up and down
	if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
		scene->mainCam->rotation.x -= camSpeed * 10;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
		scene->mainCam->rotation.x += camSpeed * 10;
	}
}



/*============================================================================
Overridden methods from LynxGame
============================================================================*/

void Game::onClose() {
	quit();
}


void Game::onResize(int width, int height) {
	glViewport(0, 0, width, height);
	scene->mainCam->aspectRatio = (float)width / (float)height;
}


void Game::onKeyPressed(KeyEvent key) {}


void Game::onKeyReleased(KeyEvent key) {
	/**
	 * Apparently, I should only use this event type of 
	 * key checking for gui types of stuff. For gameplay input,
	 * I should be checking every frame anyways. However, simple toggles
	 * fit well in here.
	*/
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
		// Make colliders render.
		for (auto &i : scene->sceneObjects) {
			if (i->collider != nullptr) i->collider->isRender = isDebugMode;
		}
		printf(isDebugMode ? "debug: on\n" : "debug: off\n");
		break;
	//======================================================================
	// QUIT
	//======================================================================
	case Keyboard::Key::Escape:
		quit();
		break;
	}

	//Spawn new cubes.
	/*if (glfwGetKey(window, GLFW_KEY_SPACE) && !isSpaceKeyDown) {
	isSpaceKeyDown = true;
	GameObject *newCube = new GameObject(GameObject::PRIMITIVE_CUBE, shaderManager->getShader("texture"), circleTexture);
	newCube->position = scene->mainCam->position + glm::vec3(0, 0, -1);
	newCube->scale = glm::vec3(0.03f);
	scene->add(newCube);
	}*/
	/*if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
	isSpaceKeyDown = false;
	}*/
}


void  Game::onMouseButtonPressed(MouseButtonEvent mouse) {

	// ENTIRE METHOD IS TEMPPPPP
	printf("screen x: %u\n", mouse.x);
	printf("screen y: %u\n", mouse.y);
	
	//GLint viewport[4]; //var to hold the viewport info
	//GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates

	////glGetDoublev(GL_MODELVIEW_MATRIX, modelview); //get the modelview info
	////glGetDoublev(GL_PROJECTION_MATRIX, projection); //get the projection matrix info
	//glGetIntegerv(GL_VIEWPORT, viewport); //get the viewport info

	//winX = (float)mouse.x;
	//winY =  (float)viewport[3] - (float)mouse.y;
	//winZ = 0;

	////get the world coordinates from the screen coordinates
	//glm::vec3 v = glm::unProject(glm::vec3(winX, winY, winZ), scene->mainCam->view, scene->mainCam->projection, glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]));


	float x = 2.0f * mouse.x / 1280 - 1;
	float y = -2.0f * mouse.y / 720 + 1;
	glm::mat4 viewProjectionInverse = glm::inverse(scene->mainCam->projection * scene->mainCam->view);

	glm::vec4 point = glm::vec4(x, y, 0, 1);
	glm::vec4 v = viewProjectionInverse * point;

	bool didIt = false;
	//float x = (2.0f * mouse.x) / 1280 - 1.0f;
	//float y = 1.0f - (2.0f * mouse.y) / 720;
	//float z = 1.0f;//We don't actually need to specify a z yet, but I put one in (for the craic).
	//glm::vec3 ray_nds = glm::vec3(x, y, z);
	//glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
	//glm::vec4 ray_eye = glm::inverse(scene->mainCam->projection) * ray_clip;
	//ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

	//glm::vec4 thing = glm::inverse(scene->mainCam->view) * ray_eye;
	//glm::vec3 ray_wor = glm::vec3(thing);
	//ray_wor = glm::normalize(ray_wor);// don't forget to normalise the vector at some point

	printf("world x: %f\n", v.x);
	printf("world y: %f\n", v.y);
	printf("world z: %f\n", v.z);

	//Ray r = Ray(glm::vec3(v.x, v.y, v.z), scene->mainCam->forward());
	Ray r = Ray(scene->mainCam->position, scene->mainCam->forward());
	//didIt = glm::intersectRaySphere(r.origin, r.direction, glm::vec3(0), 5.0f, sphere1->position, glm::vec3(0, 0, 0));

	float dis;
	didIt = r.intersects(sphere1->position, 0.5f, dis);


	if (didIt) {
		printf("omfg: %f", dis);
	}
	else {
		printf("no");
	}
	sphere1->collider->isRender = didIt;

	rayModel->position = r.origin + r.direction;
}


void  Game::onMouseButtonReleased(MouseButtonEvent mouse) {

}


void Game::init() {
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

	square1->position = glm::vec3(-0.9f, 0, 2.0f);
	square1->scale = glm::vec3(0.4f);

	square2->position = glm::vec3(0.8f, 0.1f, 2.0f);
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

	sphere1->position = glm::vec3(5.5f, -0.4f, 1.3f);
	sphere1->collider = new SphereCollider(0.5f, &sphere1->position);

	sphere2->position = glm::vec3(7.0f, -0.4f, -1.3f);
	sphere2->collider = new SphereCollider(0.75f, &sphere2->position);

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


	// TEMP
	rayModel = new GameObject(MeshManager::getInstance()->get("models/sphere.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/die.png"));
	scene->add(rayModel);
	rayModel->scale = glm::vec3(0.01f);
	plane = new Plane(glm::vec3(0, 0, -1), square1->position.z);
}


void Game::render() {
	if (!isPaused) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene->render();
	}
}


void Game::update() {
	if (!isPaused) {
		// TIPPPPPP: If i don't update camera first, models attached to cam will be lagging behind
		updateInput();
		scene->update();
		//doTest();
	}
}



void Game::doTest() {
	//scene->mainCam->position.z -= scene->mainCam->forward().z *0.02f;
	//square2->position.x += 0.02f;
	//square2->position.x += 0.02f;
	//scene->mainCam->position.z += 0.02f;
	//scene->mainCam->position.x += scene->mainCam->left().x * 0.02f;
	//printf("pos x: %f\n", square2->position.x);
	//printf("cam x: %f\n", scene->mainCam->position.x);
	/*Collision col = Collision::checkCollision(cube2->collider, sphere2->collider);
	if (col.isCollision) printf("cube2 > sphere2\n");
	col = Collision::checkCollision(sphere1->collider, sphere2->collider);
	if (col.isCollision) printf("sphere1 > sphere2\n");
	col = Collision::checkCollision(cube3->collider, cube2->collider);
	if (col.isCollision) printf("cube3 > cube2\n");*/
	// Parametric Equation (spiral)
	//sphere1->position.x = glfwGetTime() * cos(glfwGetTime());
	//sphere1->position.y = glfwGetTime() * sin(glfwGetTime());
	// Parametric Equation (circle)
	//monkey->position.x = cos((float)glfwGetTime());
	//monkey->position.y = sin((float)glfwGetTime()) + 10.0f;
	//=====================================================================
	// Check which side of plane point is on.
	//=====================================================================
	if (plane->dot(scene->mainCam->position) > 0) {
		printf("i'm in front of the plane\n");
	}
	else if (plane->dot(scene->mainCam->position) < 0) {
		printf("i'm behind the plane\n");
	}
	else {
		printf("i'm on the plane!!\n");
	}

	//=====================================================================
	// Check if Ray intersects Sphere.
	//=====================================================================
	bool didIt = false;
	float dis;
	Ray r = Ray(scene->mainCam->position, scene->mainCam->forward());
	didIt = r.intersects(sphere1->position, ((SphereCollider*)sphere1->collider)->radius, dis);
	if (didIt) {
		printf("yes: %f\n", dis);
	}
	else {
		printf("no\n");
	}
	sphere1->collider->isRender = didIt;
	rayModel->position = r.origin + r.direction;
}
