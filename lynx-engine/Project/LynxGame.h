#pragma once
// Always include glew before glfw.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// TODO: get rid of printf statements and log to my logmanager instead.
#include <iostream>

namespace lynx {

	class LynxGame {
	public:
		GLFWwindow *window;

		LynxGame();

		virtual ~LynxGame();

		void start();

		void quit();

		void createWindow(int width, int height, std::string windowName, bool isFullscreen = false);

		virtual void render() = 0;

		virtual void update() = 0;
	private:
	};

}
