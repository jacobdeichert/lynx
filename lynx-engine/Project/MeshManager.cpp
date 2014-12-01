#include "MeshManager.h"
#include "FileIO.h"
using namespace lynx;

const std::vector<GLfloat> MeshManager::TRIANGLE_VERTICES {
	// TODO: load this properly. guessed the normals for this
	-0.0693f, -0.04f,0,		0, 1, 0,	1, 0,		1, 0, 0,
	0.0693f, -0.04f, 0,		0, 1, 0,	0, 0,		0, 1, 0,
	0, 0.08f, 0,			0, 1, 0,	0.5f, 1,	0, 0, 1
};

const std::vector<GLuint> MeshManager::TRIANGLE_ELEMENTS {
	0, 1, 2
};

const std::vector<GLfloat> MeshManager::QUAD_VERTICES {
	// TODO: load this properly. guessed the normals for this
	-1, 1, 0,		0, 1, 0,		0, 1,		1, 1, 1,	// top left
	1, 1, 0,		0, 1, 0,		1, 1,		1, 1, 1,	// top right
	1, -1, 0,		0, 1, 0,		1, 0,		1, 1, 1,	// bottom right
	-1, -1, 0,		0, 1, 0,		0, 0,		1, 1, 1		// bottom left
};

const std::vector<GLuint> MeshManager::QUAD_ELEMENTS {
	0, 1, 2, 3
};


MeshManager* MeshManager::instance = nullptr;


MeshManager::MeshManager() {
	create("PRIMITIVE_TRIANGLE", TRIANGLE_VERTICES, TRIANGLE_ELEMENTS);
	create("PRIMITIVE_QUAD", QUAD_VERTICES, QUAD_ELEMENTS);
}


MeshManager::~MeshManager() {
	delete instance;
}


MeshManager* MeshManager::getInstance() {
	if (instance == nullptr) instance = new MeshManager();
	return instance;
}


void MeshManager::load(std::string meshFilePath) {
	// Ensure the mesh hasn't already been loaded.
	// Disabled because I check in the get() method.
	//if (loadedMeshes.find(meshFilePath) == loadedMeshes.end()) {
	std::string line;
	std::stringstream ss;
	std::string ssPart;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> elements;
	bool isEndOfHeader = false;

	// Open the ply file.
	FileIO *f = new FileIO();
	f->openFileIn(meshFilePath);

	while (f->readLine()) {
		line = f->getLine();

		// Read the header information if we haven't reached the end of it yet.
		if (!isEndOfHeader) {
			//if (line.substr(0, 14) == "element vertex") {
			//	// Get the element vertex value. (element vertex ###...)
			//	elementVertex = std::stoi(line.substr(15));
			//}
			//else if (line.substr(0, 12) == "element face") {
			//	// Get the element face value. (element face ###...)
			//	elementFace = std::stoi(line.substr(13));
			//}
		} // If we're done with header info, start reading vertex data.
		// If the line starts with a single 3, then it's element data.
		else if (line.substr(0, 1) != "3") {
			ss = std::stringstream(line);
			// Collect vertex data which are separated by spaces.
			while (std::getline(ss, ssPart, ' ')) {
				vertices.push_back(std::stof(ssPart));
			}
			// The last 3 values of each line are the color values.
			// Divide them by 255 to get their value between 0-1.
			vertices[vertices.size() - 1] /= 255.0f;
			vertices[vertices.size() - 2] /= 255.0f;
			vertices[vertices.size() - 3] /= 255.0f;
		} // Else it's element data, retrieve that info.
		else {
			ss = std::stringstream(line);

			// Skip the first number of every line which is a 3.
			// The 3 means the next 3 numbers are triangle data.
			std::getline(ss, ssPart, ' ');

			// Collect element data which are separated by spaces.
			while (std::getline(ss, ssPart, ' ')) {
				elements.push_back(std::stoi(ssPart));
			}
		}

		// Check if we are done reading header info.
		if (line == "end_header\n") {
			isEndOfHeader = true;
		}
	}
	f->closeFileIn();

	// Create and save the mesh.
	loadedMeshes[meshFilePath] = new Mesh(vertices, elements);
	Log::info("MeshManager> loaded mesh: \"" + meshFilePath + "\"");
}


void MeshManager::create(std::string meshName, std::vector<GLfloat> vertices, std::vector<GLuint> elements) {
	// Ensure the mesh hasn't already been loaded.
	if (loadedMeshes.find(meshName) == loadedMeshes.end()) {
		loadedMeshes[meshName] = new Mesh(vertices, elements);
		Log::info("MeshManager> loaded mesh: \"" + meshName + "\"");
	}
}


Mesh* MeshManager::get(std::string meshFilePath) {
	// Ensure the mesh hasn't already been loaded.
	if (loadedMeshes.find(meshFilePath) == loadedMeshes.end()) {
		load(meshFilePath);
	}
	return loadedMeshes[meshFilePath];
}

