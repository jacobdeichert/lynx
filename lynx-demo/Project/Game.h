#pragma once
#include <LynxGame.h>
#include <TextureManager.h>
#include <Scene.h>
#include <Collision.h>
#include <gtc/random.hpp>
using namespace lynx;

class Game : public LynxGame {
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
	

	Game();

	virtual ~Game();

	void printVersionInfo();

	void updateInput();

	virtual void onClose();
	virtual void onKeyDown(KeyCode key);
	virtual void onKeyUp(KeyCode key);
	virtual void onResize(int width, int height);
	virtual void init();
	virtual void render();
	virtual void update();
};

