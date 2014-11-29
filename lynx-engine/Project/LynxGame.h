#pragma once
#include <GL/glew.h>
#include <SFML/Window.hpp>

// TODO: get rid of printf statements and log to my logmanager instead.
#include <iostream>

namespace lynx {
	class LynxGame {
	public:
		sf::Window window;

		LynxGame();

		virtual ~LynxGame();


		void createWindow(int width, int height, std::string windowName, bool isFullscreen = false);


		void start();


		void quit();


		virtual void render() = 0;


		virtual void update() = 0;
	};
}
