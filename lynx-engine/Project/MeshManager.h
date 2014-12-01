#pragma once
#include <map>
#include "Mesh.h"
#include "FileIO.h"
#include "Logger.h"


namespace lynx {
	class MeshManager {
	public:
		~MeshManager();
		static MeshManager* getInstance();
		void create(std::string meshName, std::vector<GLfloat> vertices, std::vector<GLuint> elements);
		Mesh* get(std::string meshFilePath);
	private:
		static MeshManager* instance;
		std::map<std::string, Mesh*> loadedMeshes;
		MeshManager();
		void load(std::string meshFilePath);
		static const std::vector<GLfloat> TRIANGLE_VERTICES;
		static const std::vector<GLuint> TRIANGLE_ELEMENTS;
		static const std::vector<GLfloat> QUAD_VERTICES;
		static const std::vector<GLuint> QUAD_ELEMENTS;
	};
}
