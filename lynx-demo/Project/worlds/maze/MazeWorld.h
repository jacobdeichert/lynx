#pragma once
#include <gtc/random.hpp>
#include <LynxGame.h>
#include <Resources.h>
#include <Scene.h>
#include "MazeTile.h"
using namespace lynx;

class MazeWorld : public LynxGame {
public:
	static const int MAZE_LAYOUT[];
	Scene *scene;
	GameObject *gun;
	GameObject *sky;
	GameObject *endDoor;
	GameObject *key;
	bool isPaused = false;
	bool isDebugMode = false;
	std::vector<MazeTile*> mazeTiles;
	const float frequency = 0.02f;
	float phase = 0;// between -1 to 1
	float amp = 0.05f;
	float gunHeightOffset = 1.4f;
	float collectableHeightOffset = 1.4f;
	bool hasPickedUpGun = false;
	bool hasPickedUpKey = false;
	bool hasOpenedDoor = false;


	MazeWorld();

	virtual ~MazeWorld();

	void quit();

	void updateInput();
	void updateCameraInput();
	void initMaze();
	
	virtual void init();
	virtual void render();
	virtual void update();
	virtual void onClose();
	virtual void onResize(int width, int height);
	virtual void onKeyReleased(KeyEvent key);
};

