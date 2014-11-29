#pragma once
// TODO: get rid of printf statements and log to my logmanager instead.
#include <iostream>
#include "Window.h"

namespace lynx {
	using KeyCode = sf::Keyboard::Key;
	class LynxGame {
	public:
		LynxGame();


		virtual ~LynxGame();


		void setup(int windowWidth, int windowHeight, std::string windowName, bool isFullscreen = false);
		void quit();


		virtual void onClose() = 0;
		virtual void onKeyDown(KeyCode key) = 0;
		virtual void onKeyUp(KeyCode key) = 0;
		virtual void onResize(int width, int height) = 0;
		virtual void init() = 0;
		virtual void render() = 0;
		virtual void update() = 0;
	private:
		Window window;
		bool hasQuit;
		void beginLoop();
	};
}
