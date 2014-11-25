#pragma once
//#include <GL\glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include "Camera.h"
#include "ShaderManager.h"
#include "BoxCollider.h"


namespace lynx {
	class Scene {
	public:
		Camera *mainCam;

		std::vector<GameObject*> sceneObjects;

		glm::vec4 clearColor;

		Scene(glm::vec4 _clearColor);

		virtual ~Scene();

		void add(GameObject *_gameObject);

		void render();

		void update();
	private:
		GameObject *sphereColliderVisual = nullptr;
		GameObject *boxColliderVisual = nullptr;

		void renderObjects(std::vector<GameObject*> _objects, glm::mat4 _vp);
	};
}
