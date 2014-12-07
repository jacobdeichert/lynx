#pragma once
#include "MeshManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Collider.h"
#include "Transform.h"

namespace lynx {
	class GameObject {
	public:
		static const enum PrimitiveType { PRIMITIVE_NONE, PRIMITIVE_TRIANGLE, PRIMITIVE_QUAD };
		Mesh *mesh = nullptr;
		Shader *shader = nullptr;
		Texture *texture = nullptr;
		Collider *collider = nullptr;
		GLenum drawMode = NULL;
		bool isWireframeMode = false;

		// Start using components...
		Transform *transform = nullptr;



		GameObject();


		GameObject(PrimitiveType _primitiveType, Shader *_shader, Texture *_texture);


		GameObject(Mesh *_mesh, Shader *_shader, Texture *_texture = nullptr);


		virtual ~GameObject();


		virtual void update(glm::mat4 vp);
		//virtual void render();

	};
}
