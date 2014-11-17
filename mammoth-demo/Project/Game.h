#pragma once
#include <MammothGame.h>
#include <ShaderManager.h>
#include <TextureManager.h>
#include <Scene.h>
#include <gtc/random.hpp>
using namespace Mammoth;

class Game : public MammothGame {
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
	GameObject* sphere;
	GameObject *ground;
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

