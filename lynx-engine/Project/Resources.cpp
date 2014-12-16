#include "Resources.h"
#include "FileIO.h"
#include "Log.h"
#include <map>
#include <FreeImage.h>
using namespace lynx;

//================================================================================================
// Private
//================================================================================================

namespace {

	const std::vector<GLfloat> TRIANGLE_VERTICES {
		// TODO: load this properly. guessed the normals for this
		-0.0693f, -0.04f,0,		0, 1, 0,	1, 0,		1, 0, 0,
		0.0693f, -0.04f, 0,		0, 1, 0,	0, 0,		0, 1, 0,
		0, 0.08f, 0,			0, 1, 0,	0.5f, 1,	0, 0, 1
	};


	const std::vector<GLuint> TRIANGLE_ELEMENTS {
		0, 1, 2
	};


	const std::vector<GLfloat> QUAD_VERTICES {
		// TODO: load this properly. guessed the normals for this
		-1, 1, 0,		0, 1, 0,		0, 1,		1, 1, 1,	// top left
		1, 1, 0,		0, 1, 0,		1, 1,		1, 1, 1,	// top right
		1, -1, 0,		0, 1, 0,		1, 0,		1, 1, 1,	// bottom right
		-1, -1, 0,		0, 1, 0,		0, 0,		1, 1, 1		// bottom left
	};


	const std::vector<GLuint> QUAD_ELEMENTS {
		0, 1, 2, 3
	};


	std::map<std::string, Texture*> loadedTextures;


	std::map<std::string, Mesh*> loadedMeshes;
	

	void loadTexture(std::string filepath) {
		// Ensure the texture hasn't already been loaded.
		// Disabled because I check in the get() method.
		//if (loadedTextures.find(textureFilePath) == loadedTextures.end()) {
		GLuint textureID = NULL;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);


		// Determine the image file type.
		FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(filepath.c_str());
		if (format == FIF_UNKNOWN) {
			Log::error("TextureManager || unknown file type for texture \"" + filepath + "\"");
			return;
		}


		// Load the image.
		FIBITMAP *bitmap = FreeImage_Load(format, filepath.c_str());
		if (!bitmap) {
			Log::error("TextureManager || failed to load texture \"" + filepath + "\"");
			return;
		}


		/**
		* Convert our image up to 32 bits (8 bits per channel, Red/Green/Blue/Alpha)
		* but only if the image is not already 32 bits (i.e. 8 bits per channel).
		*/
		int bitsPerPixel = FreeImage_GetBPP(bitmap);
		FIBITMAP* bitmap32;
		if (bitsPerPixel == 32) {
			bitmap32 = bitmap;
		}
		else {
			bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
		}

		int width = FreeImage_GetWidth(bitmap32);
		int height = FreeImage_GetHeight(bitmap32);
		int colorFormat;


		/**
		* Check the color format.
		*
		* FreeImage will store the color components for a
		* pixel in the order red/green/blue on some platforms
		* but in the order blue/green/red on other platforms.
		*/
		if (FI_RGBA_RED == 0) {
			colorFormat = GL_RGBA;
		}
		else {
			colorFormat = GL_BGRA;
		}
		// Send the image to OpenGL with the determined color format.
		// TODO: move this below glGenerateMipmap???? Not sure????
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(bitmap32));
		/**
		* Mag Filter and min filter are constants that specify the filtering algorithm.
		* For the mag filter, the only options are GL_NEAREST and GL_LINEAR, giving nearest
		* neighbor and linear filtering. The default for the mag filter is GL_LINEAR, and
		* there is rarely any need to change it. For min filter, in addition to GL_NEAREST
		* and GL_LINEAR, there are four options that use mipmaps for more efficient
		* filtering. The default min filter is GL_NEAREST_MIPMAP_LINEAR, which does
		* averaging between mipmaps and nearest neighbor filtering within each mipmap. For
		* even better results, at the cost of greater inefficiency, you can use GL_LINEAR_MIPMAP_LINEAR,
		* which does averaging both between and within mipmaps. (You can research the remaining two
		* options on your own if you are curious)
		*/
		// Set the min and max filters.
		// TODO: make this a parameter...
		GLuint minFilter = GL_LINEAR_MIPMAP_LINEAR;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		// If we're using mipmaps, then we'll generate them here.
		if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST || minFilter == GL_NEAREST_MIPMAP_LINEAR || minFilter == GL_NEAREST_MIPMAP_NEAREST) {
			glGenerateMipmap(GL_TEXTURE_2D);
		}


		// TODO: for testing transparency
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);




		// Unload the 32-bit color bitmap
		FreeImage_Unload(bitmap32);
		/**
		* If we had to do a conversion to 32-bit color, then unload the original
		* non-32-bit-color version of the image data too. Otherwise, bitmap32 and
		* bitmap point at the same data, and that data's already been free'd, so
		* don't attempt to free it again! (or we'll crash).
		*/
		if (bitsPerPixel != 32) {
			FreeImage_Unload(bitmap);
		}


		// Save the texture in the map of loaded ones.
		loadedTextures[filepath] = new Texture(filepath, textureID);


		Log::info("TextureManager || loaded texture: \"" + filepath + "\"");
	}


	void loadMesh(std::string filepath) {
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
		f->openFileIn(filepath);

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
		loadedMeshes[filepath] = new Mesh(vertices, elements);
		Log::info("MeshManager || loaded mesh: \"" + filepath + "\"");
	}

}

//================================================================================================
// Public
//================================================================================================

void Resources::init() {
	//createMesh("PRIMITIVE_TRIANGLE", TRIANGLE_VERTICES, TRIANGLE_ELEMENTS);
	//createMesh("PRIMITIVE_QUAD", QUAD_VERTICES, QUAD_ELEMENTS);
}


Texture* Resources::getTexture(std::string filepath) {
	if (loadedTextures.find(filepath) == loadedTextures.end()) {
		loadTexture(filepath);
	}
	return loadedTextures[filepath];
}


Mesh* Resources::getMesh(std::string filepath) {
	// Ensure the mesh hasn't already been loaded.
	if (loadedMeshes.find(filepath) == loadedMeshes.end()) {
		loadMesh(filepath);
	}
	return loadedMeshes[filepath];
}


void Resources::createMesh(std::string meshName, std::vector<GLfloat> vertices, std::vector<GLuint> elements) {
	// Ensure the mesh hasn't already been loaded.
	if (loadedMeshes.find(meshName) == loadedMeshes.end()) {
		loadedMeshes[meshName] = new Mesh(vertices, elements);
		Log::info("MeshManager || loaded mesh: \"" + meshName + "\"");
	}
}

