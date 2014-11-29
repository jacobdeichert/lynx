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
	hasQuit = false;
}


LynxGame::~LynxGame() {
	quit();
}


void LynxGame::setup(int windowWidth, int windowHeight, std::string windowName, bool isFullscreen) {
	// TODO parse a settings manager
	window.init(windowWidth, windowHeight, windowName, isFullscreen);
	init();
	beginLoop();
}


void LynxGame::beginLoop() {
	while (window.isOpen()) {
		// Check all the window's events that were triggered since the last iteration of the loop.
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				onClose();
				quit();
				break;
			case sf::Event::Resized:
				onResize(event.size.width, event.size.height);
				break;
			case sf::Event::KeyPressed:
				onKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				onKeyUp(event.key.code);
				break;
			}
		}
		update();
		render();
		// End the current frame and display its contents on screen (internally swaps the front and back buffers).
		window.display();
	}
}


void LynxGame::quit() {
	if (!hasQuit) {
		hasQuit = true;
		if (window.isOpen()) window.close();
	}
}
