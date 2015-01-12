#include "Scene.h"
#include "BoxCollider.h"
#include "Config.h"
using namespace lynx;


Scene::Scene() {
	// Create and add the default camera to the scene.
	mainCam = new GameObject("Main Camera");
	mainCam->addComponent(new Camera(mainCam, (float)Config::getInt("window.width") / (float)Config::getInt("window.height"), glm::vec4(Config::getFloat("window.clear_color.r"), Config::getFloat("window.clear_color.g"), Config::getFloat("window.clear_color.b"), Config::getFloat("window.clear_color.a"))));
	add(mainCam);
	
	//sphereColliderVisual = new GameObject(MeshManager::getInstance()->get("models/sphere.ply"), ShaderManager::getInstance()->getShader("LynxEngineDebugShader"));
	//sphereColliderVisual->isWireframeMode = true;
	//boxColliderVisual = new GameObject(MeshManager::getInstance()->get("models/cube_1_face.ply"), ShaderManager::getInstance()->getShader("LynxEngineDebugShader"));
	//boxColliderVisual->isWireframeMode = true;
}


Scene::~Scene() {
	delete mainCam;
	//delete sphereColliderVisual;
	//delete boxColliderVisual;
}


void Scene::add(GameObject *_gameObject) {
	// Need to make sure the object isn't already in there??
	sceneObjects.push_back(_gameObject);
}



void Scene::update() {
	// Update all the scene objects.
	for (auto &i : sceneObjects) {
		i->update();
	}
}


void Scene::render() {
	// Render all the scene objects.
	for (auto &i : sceneObjects) {
		i->render();
	}
}
