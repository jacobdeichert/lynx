#include "Scene.h"
#include "ShaderManager.h"
#include "BoxCollider.h"
using namespace lynx;


Scene::Scene(glm::vec4 _clearColor, float aspectRatio) {
	mainCam = new Camera(aspectRatio);
	clearColor = _clearColor;
	// Set the clear color.
	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);

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
	// Always update cameras before other objects
	// so that the vp can be calculated.
	mainCam->update();

	// Render all the scene objects.
	for (auto &i : sceneObjects) {
		i->update();
	}
}
