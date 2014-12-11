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
	//sphere2->transform->translate(sphere2->transform->forward() *  0.01f);
	//scene->mainCam->transform->translate(scene->mainCam->transform->forward() * 0.01f);
	//sphere2->transform->translate(sphere2->transform->left() *  0.01f);
	//scene->mainCam->transform->translate(scene->mainCam->transform->left() * 0.01f);
	//sphere2->transform->translate(0, 0, 0.01f);
	//scene->mainCam->transform->translate(0, 0, 0.01f);
	//sphere2->transform->translate(0.01f, 0, 0);
	//scene->mainCam->transform->translate(0.01f, 0, 0);
	//printf("sphere: %1.2f, %1.2f, %1.2f\n", sphere2->transform->position.x, sphere2->transform->position.y, sphere2->transform->position.z);
	//printf("cam: %1.2f, %1.2f, %1.2f\n", scene->mainCam->transform->position.x, scene->mainCam->transform->position.y, scene->mainCam->transform->position.z);
	//======================================================================
	// QUICK TESTING
	//======================================================================
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad8)) {
		sphere2->transform->translate(sphere2->transform->forward() * 0.01f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad5)) {
		sphere2->transform->translate(-sphere2->transform->forward() * 0.01f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad6)) {
		sphere2->transform->translate(-sphere2->transform->left() * 0.01f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad4)) {
		sphere2->transform->translate(sphere2->transform->left() * 0.01f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad9)) {
		sphere2->transform->translate(glm::vec3(0, 0.01f, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad3)) {
		sphere2->transform->translate(-glm::vec3(0, 0.01f, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad7)) {
		sphere2->transform->rotate(0, -0.1f, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Numpad1)) {
		sphere2->transform->rotate(0, 0.1f, 0);
	}

	////======================================================================
	//// ROTATE STUFF
	////======================================================================
	//float r = 0;
	//if (Keyboard::isKeyPressed(Keyboard::Key::Equal)) {
	//	r = 3.0f;
	//} // the minus/dash/underscore key
	//else if (Keyboard::isKeyPressed(Keyboard::Key::Dash)) {
	//	r = -3.0f;
	//}

	//// Rotate X
	//if (Keyboard::isKeyPressed(Keyboard::Key::X)) {
	//	square1->transform->rotate(r, 0, 0);
	//	square2->transform->rotate(r, 0, 0);
	//	cube2->transform->rotate(r, 0, 0);
	//	sphere1->transform->rotate(r, 0, 0);
	//}
	//// Rotate Y
	//if (Keyboard::isKeyPressed(Keyboard::Key::Y)) {
	//	square1->transform->rotate(0, r, 0);
	//	square2->transform->rotate(0, r, 0);
	//	cube2->transform->rotate(0, r, 0);
	//	sphere1->transform->rotate(0, r, 0);
	//}
	//// Rotate Z
	//if (Keyboard::isKeyPressed(Keyboard::Key::Z)) {
	//	square1->transform->rotate(0, 0, r);
	//	square2->transform->rotate(0, 0, r);
	//	cube2->transform->rotate(0, 0, r);
	//	sphere1->transform->rotate(0, 0, r);
	//}


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
	if (Keyboard::isKeyPressed(Keyboard::Key::Add)) {
		scene->mainCam->transform->translate(0, camSpeed, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Subtract)) {
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


	cube1->transform->rotate(0, 0, 1);
	cube2->transform->rotate(0, 0, 3);
	cube3->transform->rotate(0, 0, 1);
}



/*============================================================================
Overridden methods from LynxGame
============================================================================*/

void Game::onClose() {
	quit();
}


void Game::onResize(int width, int height) {
	glViewport(0, 0, width, height);
	scene->mainCam->camera->aspectRatio = (float)width / (float)height;
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
	//printf("screen x: %u\n", mouse.x);
	//printf("screen y: %u\n", mouse.y);
	//
	////GLint viewport[4]; //var to hold the viewport info
	////GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates

	//////glGetDoublev(GL_MODELVIEW_MATRIX, modelview); //get the modelview info
	//////glGetDoublev(GL_PROJECTION_MATRIX, projection); //get the projection matrix info
	////glGetIntegerv(GL_VIEWPORT, viewport); //get the viewport info

	////winX = (float)mouse.x;
	////winY =  (float)viewport[3] - (float)mouse.y;
	////winZ = 0;

	//////get the world coordinates from the screen coordinates
	////glm::vec3 v = glm::unProject(glm::vec3(winX, winY, winZ), scene->mainCam->view, scene->mainCam->projection, glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]));


	//float x = 2.0f * mouse.x / 1280 - 1;
	//float y = -2.0f * mouse.y / 720 + 1;
	//glm::mat4 viewProjectionInverse = glm::inverse(scene->mainCam->projection * scene->mainCam->view);

	//glm::vec4 point = glm::vec4(x, y, 0, 1);
	//glm::vec4 v = viewProjectionInverse * point;

	//bool didIt = false;
	////float x = (2.0f * mouse.x) / 1280 - 1.0f;
	////float y = 1.0f - (2.0f * mouse.y) / 720;
	////float z = 1.0f;//We don't actually need to specify a z yet, but I put one in (for the craic).
	////glm::vec3 ray_nds = glm::vec3(x, y, z);
	////glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
	////glm::vec4 ray_eye = glm::inverse(scene->mainCam->projection) * ray_clip;
	////ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

	////glm::vec4 thing = glm::inverse(scene->mainCam->view) * ray_eye;
	////glm::vec3 ray_wor = glm::vec3(thing);
	////ray_wor = glm::normalize(ray_wor);// don't forget to normalise the vector at some point

	//printf("world x: %f\n", v.x);
	//printf("world y: %f\n", v.y);
	//printf("world z: %f\n", v.z);

	////Ray r = Ray(glm::vec3(v.x, v.y, v.z), scene->mainCam->forward());
	//Ray r = Ray(scene->mainCam->transform->position, scene->mainCam->transform->forward());
	////didIt = glm::intersectRaySphere(r.origin, r.direction, glm::vec3(0), 5.0f, sphere1->position, glm::vec3(0, 0, 0));

	//float dis;
	//didIt = r.intersects(sphere1->transform->position, 0.5f, dis);


	//if (didIt) {
	//	printf("omfg: %f", dis);
	//}
	//else {
	//	printf("no");
	//}
	//sphere1->collider->isRender = didIt;

	//rayModel->transform->position = r.origin + r.direction;
}


void  Game::onMouseButtonReleased(MouseButtonEvent mouse) {

}


void Game::init() {
	FreeImage_Initialise(true);
	scene = new Scene(glm::vec4(0, 0, 0, 1), (float)1280/(float)720);
	scene->mainCam->transform->setPosition(5, 0, -5);


	ShaderManager::getInstance()->loadShader("texture", "shaders/texture_vert.glsl", "shaders/texture_frag.glsl");
	ShaderManager::getInstance()->loadShader("color", "shaders/color_vert.glsl", "shaders/color_frag.glsl");
	//ShaderManager::getInstance()->loadShader("normal", "shaders/normal_vert.glsl", "shaders/normal_frag.glsl");
	//shaderManager->loadShader("simple", "shaders/SimpleVertexShader.glsl", "shaders/SimpleFragmentShader.glsl");
	//shaderManager->loadShader("ali", "shaders/AliVertexShader.glsl", "shaders/AliFragmentShader.glsl");



	// Initialize objects.
	scene->mainCam->transform->rotate(0, 180, 0);
	//triangle1 = new GameObject(GameObject::PRIMITIVE_TRIANGLE, ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/tron.png"));
	//square1 = new GameObject(GameObject::PRIMITIVE_QUAD, ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/jd.png"));
	//square2 = new GameObject(GameObject::PRIMITIVE_QUAD, ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/jd.png"));
	cube1 = new GameObject("cube1");
	cube1->addComponent(new Graphics(cube1, MeshManager::getInstance()->get("models/cube_1_face.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/tron.png")));
	//cube1->transform->setPosition(-0.3f, -0.2f, 0.4f);
	//cube1->transform->setScale(0.06f, 0.06f, 0.3f);
	cube1->transform->setPosition(0,0,1);
	cube1->transform->setScale(0.16f);
	//scene->add(cube1);
	scene->mainCam->transform->addChild(cube1->transform);


	cube2 = new GameObject("cube2");
	cube2->addComponent(new Graphics(cube2, MeshManager::getInstance()->get("models/cube_6_face.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/die.png")));
	cube2->transform->setPosition(2.75f, 0.4f, -0.3f);
	cube2->transform->setScale(0.4f);
	//cube2->collider = new BoxCollider(glm::vec3(0.5f), &cube2->transform->position);
	//scene->add(cube2);
	cube1->transform->addChild(cube2->transform);


	cube3 = new GameObject("cube3");
	cube3->addComponent(new Graphics(cube3, MeshManager::getInstance()->get("models/cube_1_face.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/circle.png")));
	cube3->transform->setPosition(5.75f, -0.4f, -0.3f);
	cube3->transform->setScale(0.5f);
	//cube3->collider = new BoxCollider(glm::vec3(0.5f), &cube3->transform->position);
	scene->add(cube3);


	castle = new GameObject("castle");
	castle->addComponent(new Graphics(castle, MeshManager::getInstance()->get("models/castle.ply"), ShaderManager::getInstance()->getShader("color")));
	castle->transform->setScale(100);
	scene->add(castle);


	monkey = new GameObject("monkey");
	monkey->addComponent(new Graphics(monkey, MeshManager::getInstance()->get("models/monkey.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/tron.png")));
	monkey->transform->setPosition(0, 20.0f, 0);
	monkey->transform->setRotation(-90.0f, 0, 0);
	scene->add(monkey);
	

	gun = new GameObject("gun");
	gun->addComponent(new Graphics(gun, MeshManager::getInstance()->get("models/gun.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/gun-1.png")));
	gun->transform->setPosition(0, 20, 0);
	scene->add(gun);
	// add mag to gun
	GameObject *mag = new GameObject("mag");
	mag->addComponent(new Graphics(mag, MeshManager::getInstance()->get("models/mag.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/mag-1.png")));
	gun->transform->addChild(mag->transform);


	sphere1 = new GameObject("sphere1");
	sphere1->addComponent(new Graphics(sphere1, MeshManager::getInstance()->get("models/sphere.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/purpleBall.png")));
	sphere1->transform->setPosition(5.5f, -0.4f, 1.3f);
	sphere1->collider = new SphereCollider(0.5f, &sphere1->transform->position);
	scene->add(sphere1);


	sphere2 = new GameObject("sphere2");
	sphere2->addComponent(new Graphics(sphere2, MeshManager::getInstance()->get("models/sphere.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/tron.png")));
	sphere2->transform->setPosition(7.0f, -0.4f, -1.3f);
	sphere2->collider = new SphereCollider(0.75f, &sphere2->transform->position);
	scene->add(sphere2);
	
	////ground = new GameObject(GameObject::PRIMITIVE_QUAD, ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/metal.jpg"));
	/*triangle1->transform->setPosition(0.0f, -0.2f, 0.7f);
	triangle1->transform->setScale(8);
	triangle1->transform->setRotation(0, 90, 0);

	square1->transform->setPosition(-0.9f, 0, 2.0f);
	square1->transform->setScale(0.4f);

	square2->transform->setPosition(0.8f, 0.1f, 2.0f);
	square2->transform->setScale(0.4f);
	*/
	
	/*ground->transform->setPosition(0, -8.0f, 0);
	ground->transform->setRotation(-90, 0, 0);
	ground->transform->setScale(70);

	*/
	//square1->addChild(cube1);
	//square2->transform->addChild(triangle1->transform);
	//square1->addChild(scene->mainCam);

	// Add objects to the scene.
	/*scene->add(square1);
	scene->add(square2);
	scene->add(ground);*/




	// TEMP
	/*rayModel = new GameObject(MeshManager::getInstance()->get("models/sphere.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/die.png"));
	scene->add(rayModel);
	rayModel->transform->setScale(0.01f);
	plane = new Plane(glm::vec3(0, 0, -1), square1->transform->position.z);*/
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
		doTest();
		scene->update();
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
	/*if (plane->dot(scene->mainCam->position) > 0) {
		printf("i'm in front of the plane\n");
	}
	else if (plane->dot(scene->mainCam->position) < 0) {
		printf("i'm behind the plane\n");
	}
	else {
		printf("i'm on the plane!!\n");
	}*/

	//=====================================================================
	// Check if Ray intersects Sphere.
	//=====================================================================
	/*bool didIt = false;
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
	rayModel->position = r.origin + r.direction;*/
}
