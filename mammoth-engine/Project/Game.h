#pragma once
// Include standard headers
//#include <stdio.h>
//#include <string>
// Include GLEW. Always include it before gl.h and glfw.h
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// TODO: get rid of printf statements and log to my logmanager instead.
#include <iostream>

class Game {
public:
	GLFWwindow *window;

	Game();
	~Game();


	void start();

	void quit();

	void createWindow();

	virtual void render() = 0;

	virtual void update() = 0;
private:
};

