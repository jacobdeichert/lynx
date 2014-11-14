#pragma once
// Include standard headers
//#include <stdio.h>
//#include <string>
// Include GLEW. Always include it before gl.h and glfw.h
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/random.hpp>

#include "ShaderManager.h"
#include "TextureManager.h"
#include "Scene.h"


class Game {
public:
	GLFWwindow *window;
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


	~Game();
	static Game* Game::getInstance();


	void beginLoop();

	void updateInput();

	int createWindow();

	void init();

	void printVersionInfo();

	void render();

	void update();
private:
	static Game* instance;
	Game();
};

