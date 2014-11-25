#pragma once
#include <LynxGame.h>
#include <TextureManager.h>
#include <Scene.h>
#include <SphereCollider.h>
#include <gtc/random.hpp>
using namespace lynx;

class Game : public lynx::LynxGame {
public:
	TextureManager *textureManager = TextureManager::getInstance();
	ShaderManager *shaderManager = ShaderManager::getInstance();
	MeshManager *meshManager;
	Scene *scene;
	bool isSpaceKeyDown = false;
	GameObject *triangle1;
	GameObject *square1;
	GameObject *square2;
	GameObject *cube1;
	GameObject *cube2;
	GameObject *cube3;
	GameObject *sphere;
	GameObject *monkey;
	GameObject *ground;
	GameObject *gun;
	bool isPaused = false;
	bool isPKeyDown = false;

	void updateInput();

	void init();

	void printVersionInfo();

	virtual void render();

	virtual void update();


	Game();
	virtual ~Game();
};

