#pragma once
#include <Game.h>
#include <ShaderManager.h>
#include <TextureManager.h>
#include <Scene.h>
#include <gtc/random.hpp>

class MammothGame : public Game {
public:
	TextureManager *textureManager = TextureManager::getInstance();
	ShaderManager *shaderManager = ShaderManager::getInstance();
	Scene *scene;
	bool isSpaceKeyDown = false;
	GameObject *triangle1;
	GameObject *square1;
	GameObject *square2;
	GameObject *cube1;
	GameObject *cube2;
	GameObject* sphere;
	GameObject *ground;
	glm::vec3 randomRotation;
	bool isPaused = false;
	bool isPKeyDown = false;

	void updateInput();

	void init();

	void printVersionInfo();

	virtual void render();

	virtual void update();


	MammothGame();
	~MammothGame();
};

