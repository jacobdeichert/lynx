#include "LynxGame.h"
using namespace lynx;



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
	Log::info("============================================================");
	Log::info("OpenGL Vendor: " + std::string(((char*)glGetString(GL_VENDOR))));
	Log::info("OpenGL Renderer: " + std::string(((char*)glGetString(GL_RENDERER))));
	Log::info("OpenGL Version: " + std::string(((char*)glGetString(GL_VERSION))));
	Log::info("OpenGL Shading Language Version: " + std::string(((char*)glGetString(GL_SHADING_LANGUAGE_VERSION))));
	Log::info("============================================================");
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
	shutdown();
}


void LynxGame::shutdown() {
	Log::info("game loop ended");
	Log::info("begin shutdown");
	if (!hasShutdown) {
		hasShutdown = true;
		if (window.isOpen()) {
			window.close();
			Log::info("window closed");
		}
		Log::info("shutdown complete");
		Log::deinit();
		exit(0);
	}
}
