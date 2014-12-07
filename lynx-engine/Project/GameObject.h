#pragma once
#include "Collider.h"
#include "components/Transform.h"
#include "components/Graphics.h"

namespace lynx {
	class GameObject {
	public:
		std::string name;
		Collider *collider = nullptr;

		// Start using components...
		// Transform is always added.
		Transform *transform = new Transform(this);
		Graphics *graphics = nullptr;



		GameObject(std::string name);


		virtual ~GameObject();


		virtual void update();


		void addComponent(Component *c);
		void addComponent(Graphics *g);
	};
}
