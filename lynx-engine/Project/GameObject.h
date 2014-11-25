#pragma once
#include "MeshManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Collider.h"

namespace lynx {
	class GameObject {
	public:
		static const enum PrimitiveType { PRIMITIVE_NONE, PRIMITIVE_TRIANGLE, PRIMITIVE_QUAD };
		Mesh *mesh = nullptr;
		Shader *shader = nullptr;
		Texture *texture = nullptr;
		Collider *collider = nullptr;
		GLenum drawMode = NULL;
		GameObject *parent = nullptr;
		std::vector<GameObject*> children;
		glm::mat4 model = glm::mat4();
		glm::vec3 acceleration = glm::vec3(0);
		glm::vec3 position = glm::vec3(0);
		glm::vec3 rotation = glm::vec3(0);
		glm::vec3 scale = glm::vec3(1);
		glm::vec3 velocity = glm::vec3(0);
		bool isWireframeMode = false;


		GameObject();


		GameObject(PrimitiveType _primitiveType, Shader *_shader, Texture *_texture);


		GameObject(Mesh *_mesh, Shader *_shader, Texture *_texture = nullptr);


		virtual ~GameObject();


		void addChild(GameObject *_gameObject);


		virtual glm::vec3 forward();


		virtual glm::vec3 right();
	};
}
