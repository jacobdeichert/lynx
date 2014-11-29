#include "Scene.h"
using namespace lynx;


Scene::Scene(glm::vec4 _clearColor, float aspectRatio) {
	mainCam = new Camera(aspectRatio);
	clearColor = _clearColor;
	// Set the clear color.
	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);

	sphereColliderVisual = new GameObject(MeshManager::getInstance()->get("models/sphere.ply"), ShaderManager::getInstance()->getShader("LynxEngineDebugShader"));
	sphereColliderVisual->isWireframeMode = true;
	boxColliderVisual = new GameObject(MeshManager::getInstance()->get("models/cube_1_face.ply"), ShaderManager::getInstance()->getShader("LynxEngineDebugShader"));
	boxColliderVisual->isWireframeMode = true;
}


Scene::~Scene() {
	delete mainCam;
	delete sphereColliderVisual;
	delete boxColliderVisual;
}


void Scene::add(GameObject *_gameObject) {
	// Need to make sure the object isn't already in there??
	sceneObjects.push_back(_gameObject);
}


void Scene::render() {
	// Calculate this once instead of inside the loop.
	glm::mat4 vp = mainCam->projection * mainCam->view;

	// Render all the scene objects.
	renderObjects(sceneObjects, vp);
}



void Scene::renderObjects(std::vector<GameObject*> _objects, glm::mat4 _vp) {
	// Cool C++11 way to loop through all objects in a vector.
	for (auto &i : _objects) {
		// If there is a mesh (prevents camera model from being updated here).
		if (i->mesh != nullptr) {
			// Translate to the position relative to the parent model matrix.
			if (i->parent != nullptr) {
				i->model = glm::translate(i->parent->model, i->position);
			} // If there's no parent, use the identity matrix.
			else {
				i->model = glm::translate(glm::mat4(), i->position);
			}

			// Rotate each axis.
			i->model = glm::rotate(i->model, i->rotation.x, glm::vec3(1, 0, 0));
			i->model = glm::rotate(i->model, i->rotation.y, glm::vec3(0, 1, 0));
			i->model = glm::rotate(i->model, i->rotation.z, glm::vec3(0, 0, 1));

			// Scale the model.
			i->model = glm::scale(i->model, i->scale);
			
			// Render the object with the mvp (model, view, projection matrix)
			ShaderManager::getInstance()->render(i, _vp * i->model);


			// Render the collider with the mvp if there is one.
			if (i->collider != nullptr && i->collider->isRender) {
				// Calculate position and scale for collider model. Ignore rotation.
				glm::mat4 colliderModel = glm::translate(glm::mat4(), i->position);
				
				switch (i->collider->colliderType) {
					case Collider::COLLIDER_TYPE_SPHERE:
						sphereColliderVisual->scale = glm::vec3(((SphereCollider*)i->collider)->radius * 2);
						colliderModel = glm::scale(colliderModel, sphereColliderVisual->scale);
						ShaderManager::getInstance()->render(sphereColliderVisual, _vp * colliderModel);
						break;
					case Collider::COLLIDER_TYPE_AABB:
						boxColliderVisual->scale = ((BoxCollider*)i->collider)->scale;
						colliderModel = glm::scale(colliderModel, boxColliderVisual->scale);
						ShaderManager::getInstance()->render(boxColliderVisual, _vp * colliderModel);
						break;
				}
			}
		}
		// Render any children.
		if (i->children.size() > 0) renderObjects(i->children, _vp);
	}
}



void Scene::update() {
	mainCam->update();
}