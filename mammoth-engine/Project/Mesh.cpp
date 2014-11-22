#include "Mesh.h"
using namespace lynx;


Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> elements) {
	activeShaderID = NULL;

	// Vertex array object (holds vbos).
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertex buffer object (holds vertices).
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);


	// Need this for drawing elements
	numElements = elements.size();

	// Element buffer object (holds indices).
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements * sizeof(GLuint), &elements[0], GL_STATIC_DRAW);

	// TODO: Make sure we disable and unbind everything to prevent rendering issues later???
	/*glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
	/*glDisableVertexAttribArray(positionAttribID);
	glDisableVertexAttribArray(colorAttribID);*/
}


Mesh::~Mesh() {}
