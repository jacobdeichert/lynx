#pragma once


namespace lynx {
	class GameObject; // Forward declare
	class Component {
	public:
		GameObject *gameObject = nullptr;
		Component(GameObject *gameObject);
		virtual ~Component();

		virtual void update() = 0;
	};
}
