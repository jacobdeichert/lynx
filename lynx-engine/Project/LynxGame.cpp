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



LynxGame::LynxGame() {}


LynxGame::~LynxGame() {
	if (window.isOpen()) quit();
}


void LynxGame::createWindow(int width, int height, std::string windowName, bool isFullscreen) {
	printf("game start \n");
	/**
	 * DEFAULT SFML WINDOW SETTINGS
	 * sf::ContextSettings settings;
	 * settings.depthBits = 24;
	 * settings.stencilBits = 0;
	 * settings.antialiasingLevel = 0;
	 * settings.majorVersion = 4;
	 * settings.minorVersion = 4;
	*/
	GLuint style = sf::Style::Default;
	if (isFullscreen) sf::Style::Fullscreen;
	window.create(sf::VideoMode(width, height), windowName.c_str(), style);
	window.setVerticalSyncEnabled(true);
	// Limit the framerate to 60 frames per second.
	window.setFramerateLimit(60);

	/*
		GLEW has a problem with core contexts. It calls
		glGetString(GL_EXTENSIONS), which causes GL_INVALID_ENUM
		on GL3.2 core context as soon as glewInit() is called.
		It also doesn't fetch the function pointers. The solution
		is for GLEW to use glGetStringi instead. The current version
		of GLEW is 1.10.0 but they still haven't correct it.
		The glError() is #1280.
	*/
	glewExperimental = GL_TRUE; // Needed in core profile.
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		//Problem: glewInit failed, something is seriously wrong.
		printf("glewInit failed.");
	}
}


void LynxGame::start() {
	// Enable OpenGL stuff.
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	// Accept fragment if it's closer to the camera than the former one.
	glDepthFunc(GL_LESS);

	while (window.isOpen()) {
		// Check all the window's events that were triggered since the last iteration of the loop.
		sf::Event event;
		while (window.pollEvent(event)) {
			// Close event occured.
			if (event.type == sf::Event::Closed) {
				quit();
			} // Window resize occured.
			else if (event.type == sf::Event::Resized) {
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update();
		render();
		// End the current frame and display its contents on screen (internally swaps the front and back buffers).
		window.display();
	}
}


void LynxGame::quit() {
	printf("game quit");
	window.close();
}
