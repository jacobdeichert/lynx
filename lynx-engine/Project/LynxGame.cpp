#include "LynxGame.h"
using namespace lynx;

/*============================================================================================
- tutorial, left off here http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
- http://open.gl

- good example repos
- https://github.com/nikagra/opengl-demo
- https://github.com/dot-bin/Fun-with-OpenGL
- https://github.com/tumanoid/OpenGL-4.3-exploration

- cool object viewer https://github.com/hardware/ObjectViewer
- good tuts https://github.com/giawa/opengl4tutorials
============================================================================================*/



LynxGame::LynxGame() {
	hasShutdown = false;
}


LynxGame::~LynxGame() {
	shutdown();
}


void LynxGame::setup(int windowWidth, int windowHeight, std::string windowName, std::string logFilename, bool isFullscreen) {
	// TODO parse a settings manager
	Log::init(logFilename);
	window.init(windowWidth, windowHeight, windowName, isFullscreen);
	Log::info("begin initializing game");
	init();
	beginLoop();
}


void LynxGame::beginLoop() {
	Log::info("begin game loop");
	while (window.isOpen()) {
		// Check all the window's events that were triggered since the last iteration of the loop.
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				Log::info("window event: closed");
				onClose();
				shutdown();
				break;
			case sf::Event::Resized:
				Log::info("window event: resized");
				onResize(event.size.width, event.size.height);
				break;
			case sf::Event::KeyPressed:
				onKeyPressed(event.key);
				break;
			case sf::Event::KeyReleased:
				onKeyReleased(event.key);
				break;
			}
		}
		update();
		render();
		// End the current frame and display its contents on screen (internally swaps the front and back buffers).
		window.display();
	}
}


void LynxGame::shutdown() {
	if (!hasShutdown) {
		hasShutdown = true;
		if (window.isOpen()) window.close();
		exit(0);
	}
}
