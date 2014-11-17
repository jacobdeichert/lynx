#include "Game.h"

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



Game::Game() {}

Game::~Game() {
	glfwTerminate();
}


void Game::createWindow() {
	printf("game start \n");

	if (!glfwInit()) {
		printf("Failed to initialize GLFW\n");
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// We want OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	// To make MacOS happy; should not be needed
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 

	//We don't want the old OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context.
	window = glfwCreateWindow(1280, 720, "OpenGL/GLFW", nullptr, nullptr); // Windowed
	//window = glfwCreateWindow(1920, 1080, "OpenGL/GLFW", glfwGetPrimaryMonitor(), nullptr); // Fullscreen

	if (window == NULL) {
		printf("Failed to open GLFW window\n");
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	// Needed in core profile
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("Failed to initialize GLEW\n");
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	// Accept fragment if it's closer to the camera than the former one.
	glDepthFunc(GL_LESS);
}


void Game::quit() {
	printf("game quit");
	glfwTerminate();
}


void Game::start() {
	// THE LOOP
	// TODO: get an fps timer going and properly
	// do a loop
	do {
		update();
		render();

		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	} // Check if the ESC key was pressed or the window was closed.
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
	quit();
}
