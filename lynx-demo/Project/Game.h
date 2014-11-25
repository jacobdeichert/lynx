#pragma once
#include <LynxGame.h>
#include <TextureManager.h>
#include <Scene.h>
#include <BoxCollider.h>
#include <gtc/random.hpp>
using namespace lynx;

class Game : public lynx::LynxGame {
public:
	Scene *scene;
	GameObject *triangle1;
	GameObject *square1;
	GameObject *square2;
	GameObject *cube1;
	GameObject *cube2;
	GameObject *cube3;
	GameObject *sphere1;
	GameObject *sphere2;
	GameObject *monkey;
	GameObject *ground;
	GameObject *gun;
	bool isPaused = false;
	bool isDebugMode = false;
	bool isSpaceKeyDown = false;
	bool isPKeyDown = false;
	bool isTabKeyDown = false;

	void updateInput();

	void init();

	void printVersionInfo();

	virtual void render();

	virtual void update();


	Game();
	virtual ~Game();
};

