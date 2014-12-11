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


		// Transform is always added.
		Transform *transform = new Transform(this);
		Graphics *graphics = nullptr;
		/**
		 * Cameras are simply GameObjects with a
		 * Camera component.
		 */
		Camera *camera = nullptr;


		GameObject(std::string name);


		virtual ~GameObject();


		virtual void update();


		virtual void render();


		// TODO: Make this method add any component later on?
		void addComponent(Component *c);


		void addComponent(Graphics *g);


		void addComponent(Camera *c);
	};
}
