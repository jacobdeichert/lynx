#pragma once
#include <map>
#include "Mesh.h"
#include "FileIO.h"


namespace Mammoth {
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

		static const std::vector<GLfloat> TRIANGLE_VERTICES;
		static const std::vector<GLuint> TRIANGLE_ELEMENTS;
		static const std::vector<GLfloat> QUAD_VERTICES;
		static const std::vector<GLuint> QUAD_ELEMENTS;
	};
}
//const GLfloat PrimitiveObject::PRIMITIVE_VERTICES[NUM_VERTICES_TOTAL][3] = {
//	// perfect equilateral triangle 
//	{ -0.0693f, -0.04f, 0 },
//	{ 0.0693f, -0.04f, 0 },
//	{ 0.0f, 0.08f, 0 },
//
