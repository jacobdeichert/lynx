#include "MazeTile.h"
#include <Resources.h>

MazeTile::MazeTile(TileType tileType, glm::vec3 position) : GameObject("tile") {
	this->tileType = tileType;
	transform->position = position;
	transform->scale = glm::vec3(2);

	std::string textureName;
	
	switch (tileType) {
	case WALL:
		textureName = "textures/tron.png";
		break;
	case FLOOR:
		textureName = "textures/tile-red.jpg";
		break;
	}

	addComponent(new Graphics(this, Resources::getMesh("models/cube_1_face.ply"), Resources::getShader("texture"), Resources::getTexture(textureName)));
}


MazeTile::~MazeTile(){}
