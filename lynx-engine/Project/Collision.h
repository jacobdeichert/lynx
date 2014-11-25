#pragma once
#include "BoxCollider.h"

namespace lynx {
	class Collision {
	public:
		bool isCollision = false;
		Collision();
		Collision(bool _isCollision);
		~Collision();
		static Collision checkCollision(Collider *collider1, Collider *collider2);
		//bool checkCollision(std::vector<Collider*> colliders);
	private:
		static Collision checkAABBToAABB(BoxCollider *box1, BoxCollider *box2);
		static Collision checkAABBToSphere(BoxCollider *box, SphereCollider *sphere);
		static Collision checkSphereToSphere(SphereCollider *sphere1, SphereCollider *sphere2);
	};
}