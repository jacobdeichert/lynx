#pragma once
#include <LynxGame.h>
#include <Scene.h>
//#include <Ray.h>
//#include <Plane.h>
using namespace lynx;

class LightShaderWorld : public LynxGame {
public:
	Scene *scene;
	GameObject *cube1;
	GameObject *cube2;
	GameObject *cube3;
	GameObject *sphere1;
	GameObject *sphere2;
	GameObject *monkey;
	GameObject *gun;
	GameObject *castle;
	bool isPaused = false;
	bool isDebugMode = false;


	LightShaderWorld();

	virtual ~LightShaderWorld();

	void quit();

	void updateInput();

	
	virtual void init();
	virtual void render();
	virtual void update();
	virtual void onClose();
	virtual void onResize(int width, int height);
	//virtual void onLostFocus();
	//virtual void onGainedFocus();
	//virtual void onTextEntered();
	virtual void onKeyPressed(KeyEvent key);
	virtual void onKeyReleased(KeyEvent key);
	virtual void onMouseButtonPressed(MouseButtonEvent mouse);
	virtual void onMouseButtonReleased(MouseButtonEvent mouse);
	/*virtual void onMouseWheelMoved();
	virtual void onMouseMoved();
	virtual void onMouseEntered();
	virtual void onMouseLeft();*/
};


/*
GameObject *triangle1;
GameObject *square1;
GameObject *square2;
GameObject *ground;

ground = new GameObject(GameObject::PRIMITIVE_QUAD, ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/metal.jpg"));
ground->transform->setPosition(0, -8.0f, 0);
ground->transform->setRotation(-90, 0, 0);
ground->transform->setScale(70);
scene->add(ground);


triangle1 = new GameObject(GameObject::PRIMITIVE_TRIANGLE, ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/tron.png"));
triangle1->transform->setPosition(0.0f, -0.2f, 0.7f);
triangle1->transform->setScale(8);
triangle1->transform->setRotation(0, 90, 0);

square1 = new GameObject(GameObject::PRIMITIVE_QUAD, ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/jd.png"));
square1->transform->setPosition(-0.9f, 0, 2.0f);
square1->transform->setScale(0.4f);
scene->add(square1);

square2 = new GameObject(GameObject::PRIMITIVE_QUAD, ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/jd.png"));
square2->transform->setPosition(0.8f, 0.1f, 2.0f);
square2->transform->setScale(0.4f);
square2->transform->addChild(triangle1->transform);
scene->add(square2);


//======================================================================
// ROTATE STUFF
//======================================================================
float r = 0;
if (Keyboard::isKeyPressed(Keyboard::Key::Equal)) {
	r = 3.0f;
} // the minus/dash/underscore key
else if (Keyboard::isKeyPressed(Keyboard::Key::Dash)) {
	r = -3.0f;
}

// Rotate X
if (Keyboard::isKeyPressed(Keyboard::Key::X)) {
	square1->transform->rotate(r, 0, 0);
	square2->transform->rotate(r, 0, 0);
	cube2->transform->rotate(r, 0, 0);
	sphere1->transform->rotate(r, 0, 0);
}
// Rotate Y
if (Keyboard::isKeyPressed(Keyboard::Key::Y)) {
	square1->transform->rotate(0, r, 0);
	square2->transform->rotate(0, r, 0);
	cube2->transform->rotate(0, r, 0);
	sphere1->transform->rotate(0, r, 0);
}
// Rotate Z
if (Keyboard::isKeyPressed(Keyboard::Key::Z)) {
	square1->transform->rotate(0, 0, r);
	square2->transform->rotate(0, 0, r);
	cube2->transform->rotate(0, 0, r);
	sphere1->transform->rotate(0, 0, r);
}
*/



/*
// TEMP
GameObject *rayModel;// TEMP
Plane* plane;
rayModel = new GameObject(MeshManager::getInstance()->get("models/sphere.ply"), ShaderManager::getInstance()->getShader("texture"), TextureManager::getInstance()->get("textures/die.png"));
scene->add(rayModel);
rayModel->transform->setScale(0.01f);
plane = new Plane(glm::vec3(0, 0, -1), square1->transform->position.z);
void doTest();
*/






/*
void LightShaderWorld::doTest() {
//scene->mainCam->position.z -= scene->mainCam->forward().z *0.02f;
//square2->position.x += 0.02f;
//square2->position.x += 0.02f;
//scene->mainCam->position.z += 0.02f;
//scene->mainCam->position.x += scene->mainCam->left().x * 0.02f;
//printf("pos x: %f\n", square2->position.x);
//printf("cam x: %f\n", scene->mainCam->position.x);

Collision col = Collision::checkCollision(cube2->collider, sphere2->collider);
if (col.isCollision) printf("cube2 > sphere2\n");
col = Collision::checkCollision(sphere1->collider, sphere2->collider);
if (col.isCollision) printf("sphere1 > sphere2\n");
col = Collision::checkCollision(cube3->collider, cube2->collider);
if (col.isCollision) printf("cube3 > cube2\n");


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
}*/
