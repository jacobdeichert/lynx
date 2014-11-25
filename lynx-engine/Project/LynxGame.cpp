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
	glfwTerminate();
}


void LynxGame::createWindow(int width, int height, bool isFullscreen) {
	printf("game start \n");

	if (!glfwInit()) {
		printf("Failed to initialize GLFW\n");
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// We want OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// To make MacOS happy; should not be needed
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	// Open a window or fullscreen and create its OpenGL context.
	if (isFullscreen) {
		window = glfwCreateWindow(width, height, "OpenGL/GLFW", glfwGetPrimaryMonitor(), nullptr); // Fullscreen
	}
	else {
		window = glfwCreateWindow(width, height, "OpenGL/GLFW", nullptr, nullptr); // Windowed
	}

	if (window == NULL) {
		printf("Failed to open GLFW window\n");
		glfwTerminate();
	}



	glfwMakeContextCurrent(window);

	/*
		GLEW has a problem with core contexts. It calls
		glGetString(GL_EXTENSIONS), which causes GL_INVALID_ENUM
		on GL3.2 core context as soon as glewInit() is called.
		It also doesn't fetch the function pointers. The solution
		is for GLEW to use glGetStringi instead. The current version
		of GLEW is 1.10.0 but they still haven't correct it.
		The glError() is #1280.
	*/
	// Needed in core profile
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		//Problem: glewInit failed, something is seriously wrong.
		printf("glewInit failed.");
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	// Accept fragment if it's closer to the camera than the former one.
	glDepthFunc(GL_LESS);
}


void LynxGame::quit() {
	printf("game quit");
	glfwTerminate();
}


void LynxGame::start() {
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
