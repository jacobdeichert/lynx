#pragma once
#include <map>
#include "Mesh.h"
#include "FileIO.h"


class MeshManager {
public:
	~MeshManager();
	static MeshManager* getInstance();
	void load(std::string meshNameID, std::string filepath);
	void create(std::string meshNameID, std::vector<GLfloat> vertices, std::vector<GLuint> elements);
	Mesh* get(std::string meshNameID);
private:
	static MeshManager* instance;
	std::map<std::string, Mesh*> loadedMeshes;
	MeshManager();

	static const std::vector<GLfloat> CUBE_VERTICES;
	static const std::vector<GLuint> CUBE_ELEMENTS;
	static const std::vector<GLfloat> TRIANGLE_VERTICES;
	static const std::vector<GLuint> TRIANGLE_ELEMENTS;
	static const std::vector<GLfloat> QUAD_VERTICES;
	static const std::vector<GLuint> QUAD_ELEMENTS;
	static const std::vector<GLfloat> SPHERE_VERTICES;
	static const std::vector<GLuint> SPHERE_ELEMENTS;
};



//
//const GLfloat PrimitiveObject::PRIMITIVE_VERTICES[NUM_VERTICES_TOTAL][3] = {
//	// perfect equilateral triangle 
//	{ -0.0693f, -0.04f, 0 },
//	{ 0.0693f, -0.04f, 0 },
//	{ 0.0f, 0.08f, 0 },
//
//
//	// quad
//	{ -0.1f, -0.1f, 0 },
//	{ 0.1f, -0.1f, 0 },
//	{ 0.1f, 0.1f, 0 },
//	{ -0.1f, 0.1f, 0 },
//
//
//	// cube
//
//	// front face
//	{ -1, 1, 1 }, // triangle 1		// |\ 
//	{ -1, -1, 1 },					// | \ 
//	{ 1, -1, 1 },					// |__\ 
//	{ -1, 1, 1 }, // triangle 2		// \  |
//	{ 1, 1, 1 },					//  \ |
//	{ 1, -1, 1 },					//   \|
//
//	// right face
//	{ 1, 1, 1 },
//	{ 1, -1, 1 },
//	{ 1, -1, -1 },
//	{ 1, 1, 1 },
//	{ 1, 1, -1 },
//	{ 1, -1, -1 },
//
//	// back face
//	{ -1, 1, -1 },
//	{ -1, -1, -1 },
//	{ 1, -1, -1 },
//	{ -1, 1, -1 },
//	{ 1, 1, -1 },
//	{ 1, -1, -1 },
//
//	// left face
//	{ -1, 1, 1 },
//	{ -1, -1, 1 },
//	{ -1, -1, -1 },
//	{ -1, 1, 1 },
//	{ -1, 1, -1 },
//	{ -1, -1, -1 },
//
//	// top face
//	{ -1, 1, -1 },
//	{ -1, 1, 1 },
//	{ 1, 1, 1 },
//	{ -1, 1, -1 },
//	{ 1, 1, -1 },
//	{ 1, 1, 1 },
//
//	// bottom face
//	{ -1, -1, -1 },
//	{ -1, -1, 1 },
//	{ 1, -1, 1 },
//	{ -1, -1, -1 },
//	{ 1, -1, -1 },
//	{ 1, -1, 1 }
//};
//
//
//const GLfloat PrimitiveObject::PRIMITIVE_COLORS[NUM_VERTICES_TOTAL][3] = {
//	// triangle
//	{ 0.583f, 0.771f, 0.014f },
//	{ 0.609f, 0.115f, 0.436f },
//	{ 0.327f, 0.483f, 0.844f },
//
//	// quad
//	{ 0.822f, 0.569f, 0.201f },
//	{ 0.435f, 0.602f, 0.223f },
//	{ 0.310f, 0.747f, 0.185f },
//	{ 0.597f, 0.770f, 0.761f },
//
//	// cube
//	{ 1, 0, 0 },
//	{ 1, 0, 0 },
//	{ 1, 0, 0 },
//	{ 1, 0, 0 },
//	{ 1, 0, 0 },
//	{ 1, 0, 0 },
//
//	{ 0, 1, 0 },
//	{ 0, 1, 0 },
//	{ 0, 1, 0 },
//	{ 0, 1, 0 },
//	{ 0, 1, 0 },
//	{ 0, 1, 0 },
//
//	{ 0, 0, 1 },
//	{ 0, 0, 1 },
//	{ 0, 0, 1 },
//	{ 0, 0, 1 },
//	{ 0, 0, 1 },
//	{ 0, 0, 1 },
//
//	{ 1, 1, 0 },
//	{ 1, 1, 0 },
//	{ 1, 1, 0 },
//	{ 1, 1, 0 },
//	{ 1, 1, 0 },
//	{ 1, 1, 0 },
//
//	{ 1, 0, 1 },
//	{ 1, 0, 1 },
//	{ 1, 0, 1 },
//	{ 1, 0, 1 },
//	{ 1, 0, 1 },
//	{ 1, 0, 1 },
//
//	{ 0, 1, 1 },
//	{ 0, 1, 1 },
//	{ 0, 1, 1 },
//	{ 0, 1, 1 },
//	{ 0, 1, 1 },
//	{ 0, 1, 1 },
//};
