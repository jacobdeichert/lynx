#pragma once
#include <GameObject.h>
using namespace lynx;

class MazeTile : public GameObject {
public:
	enum TileType { WALL, FLOOR };

	TileType tileType;
	
	MazeTile(TileType tileType, glm::vec3 position);


	virtual ~MazeTile();
};

