#pragma once
#include <LynxGame.h>
#include <TextureManager.h>
#include <Scene.h>
#include <Collision.h>
#include <gtc/random.hpp>
//#include <Ray.h>
//#include <Plane.h>
#include <ShaderManager.h>
using namespace lynx;

class Game : public LynxGame {
public:
	Scene *scene;
	//GameObject *triangle1;
	//GameObject *square1;
	//GameObject *square2;
	GameObject *cube1;
	GameObject *cube2;
	GameObject *cube3;
	GameObject *sphere1;
	GameObject *sphere2;
	GameObject *monkey;
	GameObject *ground;
	GameObject *gun;
	GameObject *castle;
	bool isPaused = false;
	bool isDebugMode = false;

	//GameObject *rayModel;// TEMP
	//Plane* plane;
	void doTest();
	

	Game();

	virtual ~Game();

	void quit();

	void updateInput();

	
	virtual void init();
	virtual void render();
	virtual void update();
	virtual void onClose();
	virtual void onResize(int width, int height);
	//virtual void onLostFocus();
	//virtual void onGainedFocus();
	//virtual void onTextEntered();
	virtual void onKeyPressed(KeyEvent key);
	virtual void onKeyReleased(KeyEvent key);
	virtual void onMouseButtonPressed(MouseButtonEvent mouse);
	virtual void onMouseButtonReleased(MouseButtonEvent mouse);
	/*virtual void onMouseWheelMoved();
	virtual void onMouseMoved();
	virtual void onMouseEntered();
	virtual void onMouseLeft();*/
};

