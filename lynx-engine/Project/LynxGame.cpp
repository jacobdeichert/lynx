#include "LynxGame.h"
#include <GL/glew.h>
#include "Config.h"
#include "Resources.h"
#include "Log.h"
using namespace lynx;



LynxGame::LynxGame() {
	hasShutdown = false;
	

}


LynxGame::~LynxGame() {
	shutdown();
}


void LynxGame::setup() {
	Log::init();
	Config::init();
	window.init();
	Resources::init();
	Log::info("LynxGame || begin initializing game");
	init();
	beginLoop();
}


void LynxGame::beginLoop() {
	Log::info("LynxGame || begin game loop");
	while (window.isOpen()) {
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << "OpenGL error: " << err << std::endl;
		}

		// Check all the window's events that were triggered since the last iteration of the loop.
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				Log::info("LynxGame || window event: closed");
				onClose();
				shutdown();
				break;
			case sf::Event::Resized:
				Log::info("LynxGame || window event: resized");
				onResize(event.size.width, event.size.height);
				break;
			case sf::Event::KeyPressed:
				onKeyPressed(event.key);
				break;
			case sf::Event::KeyReleased:
				onKeyReleased(event.key);
				break;
			case sf::Event::MouseButtonPressed:
				onMouseButtonPressed(event.mouseButton);
				break;
			case sf::Event::MouseButtonReleased:
				onMouseButtonReleased(event.mouseButton);
				break;
			}
		}
		
		update();
		render();
		// End the current frame and display its contents on screen (internally swaps the front and back buffers).
		window.display();
	}
	shutdown();
}


void LynxGame::shutdown() {
	Log::info("LynxGame || game loop ended");
	Log::info("LynxGame || begin shutdown");
	if (!hasShutdown) {
		hasShutdown = true;
		if (window.isOpen()) {
			window.close();
			Log::info("LynxGame || window closed");
		}
		Log::info("LynxGame || shutdown complete");
		Log::deinit();
		exit(0);
	}
}
