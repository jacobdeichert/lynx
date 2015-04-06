//#include "MazeTile.h"
//using namespace glm;
//
//MazeTile::MazeTile() {}
//
//
//MazeTile::MazeTile(TileType tileType, glm::vec3 position) {
//	this->tileType = tileType;
//	this->position = position;
//	this->scale = vec3(2);
//	mesh = lynx::MeshManager::getInstance()->get("models/cube_1_face.ply");
//	shader = lynx::ShaderManager::getInstance()->getShader("texture");
//	drawMode = GL_TRIANGLES;
//	switch (tileType) {
//	case WALL:
//		texture = lynx::TextureManager::getInstance()->get("textures/wall.png");
//		break;
//	case FLOOR:
//		texture = lynx::TextureManager::getInstance()->get("textures/floor.jpg");
//		break;
//	}
//}
//
//
//MazeTile::~MazeTile(){}
