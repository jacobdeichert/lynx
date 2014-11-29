#include "Window.h"
using namespace lynx;



Window::Window() {
	


}


Window::~Window() {
}



void Window::create(int width, int height, std::string windowName, bool isFullscreen) {
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
	sf::Window::create(sf::VideoMode(width, height), windowName.c_str(), style);
	setVerticalSyncEnabled(true);
	// Limit the framerate to 60 frames per second.
	setFramerateLimit(60);
}

void Window::onCreate() {
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

	// Enable default OpenGL stuff.
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	// Accept fragment if it's closer to the camera than the former one.
	glDepthFunc(GL_LESS);
}
