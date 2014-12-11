#pragma once
#include "Collider.h"
#include "components/Transform.h"
#include "components/Graphics.h"
#include "components/Camera.h"

namespace lynx {
	class GameObject {
	public:
		std::string name;
		Collider *collider = nullptr;

		// Start using components...
		// Transform is always added.
		Transform *transform = new Transform(this);
		Graphics *graphics = nullptr;
		Camera *camera = nullptr;


		GameObject(std::string name);


		virtual ~GameObject();


		virtual void update();
		virtual void render();


		void addComponent(Component *c);
		void addComponent(Graphics *g);
		void addComponent(Camera *c);
	};
}
