#pragma once
#include <GL/glew.h>
#include "Component.h"


namespace lynx {
	class Mesh;
	class Texture;
	class Shader;
	class Graphics : public Component {
	public:
		Mesh *mesh = nullptr;
		Texture *texture = nullptr;
		Shader *shader = nullptr;
		GLenum drawMode;
		bool isWireframeMode = false;


		Graphics(GameObject *gameObject, Mesh *mesh, Shader *shader, Texture *texture = nullptr, GLenum drawMode = GL_TRIANGLES);


		virtual ~Graphics();


		virtual void update();
	};
}
