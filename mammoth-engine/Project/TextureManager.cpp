#include "TextureManager.h"
using namespace lynx;

TextureManager* TextureManager::instance = nullptr;



TextureManager::TextureManager() {}



TextureManager::~TextureManager() {}



TextureManager* TextureManager::getInstance() {
	if (instance == nullptr) {
		instance = new TextureManager();
	}
	return instance;
}



void TextureManager::load(std::string textureNameID, std::string filePath) {
	// Ensure the texture hasn't already been loaded.
	if (loadedTextures.find(textureNameID) == loadedTextures.end()) {
		GLuint textureID = NULL;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);


		// Determine the image file type.
		FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(filePath.c_str());
		if (format == FIF_UNKNOWN) {
			printf("Unknown file type for texture file: %s\n", filePath);
			return;
		}


		// Load the image.
		FIBITMAP *bitmap = FreeImage_Load(format, filePath.c_str());
		if (!bitmap) {
			printf("Failed to load image: %s\n", filePath);
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
		 *
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


		// for testing transparency
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
		loadedTextures[textureNameID] = new Texture(textureNameID, textureID);
	}
}



Texture* TextureManager::get(std::string textureNameID) {
	return loadedTextures[textureNameID];
}

