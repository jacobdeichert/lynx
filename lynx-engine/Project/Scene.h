#pragma once
#include <glm.hpp>
#include <vector>
#include "GameObject.h"


namespace lynx {
	class Scene {
	public:
		GameObject *mainCam = nullptr;

		std::vector<GameObject*> sceneObjects;
		
		Scene();

		virtual ~Scene();

		void add(GameObject *_gameObject);

		void render();

		void update();
	private:
		//GameObject *sphereColliderVisual = nullptr;
		//GameObject *boxColliderVisual = nullptr;
	};
}
