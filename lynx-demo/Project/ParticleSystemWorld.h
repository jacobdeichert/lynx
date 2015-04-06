#pragma once
#include <LynxGame.h>
#include <Scene.h>
using namespace lynx;

class ParticleSystemWorld : public LynxGame {
public:
	Scene *scene;
	GameObject *particleSystem;
	bool isPaused = false;
	bool isDebugMode = false;


	ParticleSystemWorld();

	virtual ~ParticleSystemWorld();

	void quit();

	void updateInput();

	void updateCamera();

	
	virtual void init();
	virtual void render();
	virtual void update();
	virtual void onClose();
	virtual void onResize(int width, int height);
	//virtual void onLostFocus();
	//virtual void onGainedFocus();
	//virtual void onTextEntered();
	//virtual void onKeyPressed(KeyEvent key);
	virtual void onKeyReleased(KeyEvent key);
	//virtual void onMouseButtonPressed(MouseButtonEvent mouse);
	//virtual void onMouseButtonReleased(MouseButtonEvent mouse);
	//virtual void onMouseWheelMoved();
	//virtual void onMouseMoved();
	//virtual void onMouseEntered();
	//virtual void onMouseLeft();
};
