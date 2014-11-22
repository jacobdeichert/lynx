#pragma once
//#include <GL\glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include "Camera.h"
#include "ShaderManager.h"


namespace lynx {
	class Scene {
	public:
		ShaderManager *shaderManager = ShaderManager::getInstance();
		Camera *mainCam;

		Scene();
		~Scene();

		void add(GameObject *_gameObject);

		void render();

		void update();
	private:
		std::vector<GameObject*> sceneObjects;

		void renderObjects(std::vector<GameObject*> _objects, glm::mat4 _vp);
	};
}
