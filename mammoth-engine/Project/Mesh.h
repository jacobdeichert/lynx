#pragma once
#include <vector>
#include <GL\glew.h>


namespace lynx {
	class Mesh {
	public:
		GLuint numElements;
		GLuint vao;
		GLuint vbo;
		GLuint ebo;
		GLuint activeShaderID;


		Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> elements);
		~Mesh();
	};
}

