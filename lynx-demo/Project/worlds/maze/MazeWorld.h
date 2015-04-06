//#pragma once
//#include <gtc/random.hpp>
//#include <LynxGame.h>
//#include <Resources.h>
//#include <Scene.h>
//#include <Collision.h>
////#include <Ray.h>
////#include <Plane.h>
//#include "MazeTile.h"
//using namespace lynx;
//
//class Game : public LynxGame {
//public:
//	static const int MAZE_LAYOUT[];
//	Scene *scene;
//	sf::Clock clock;
//	/*GameObject *triangle1;
//	GameObject *square1;
//	GameObject *square2;
//	GameObject *cube2;
//	GameObject *cube3;
//	GameObject *sphere1;
//	GameObject *sphere2;*/
//	GameObject *monkey;
//	GameObject *gun;
//	GameObject *sky;
//	GameObject *endDoor;
//	GameObject *key;
//	bool isPaused = false;
//	bool isDebugMode = false;
//	std::vector<MazeTile*> mazeTiles;
//	const float frequency = 0.02f;
//	float phase = 0;// between -1 to 1
//	float amp = 0.05f;
//	float gunHeightOffset = 1.4f;
//	float collectableHeightOffset = 1.4f;
//	bool hasPickedUpGun = false;
//	bool hasPickedUpKey = false;
//	bool hasOpenedDoor = false;
//
//
//	
//
//	Game();
//
//	virtual ~Game();
//
//	void quit();
//
//	void updateInput();
//	void updateCameraInput();
//	void initMaze();
//	
//	virtual void init();
//	virtual void render();
//	virtual void update();
//	virtual void onClose();
//	virtual void onResize(int width, int height);
//	//virtual void onLostFocus();
//	//virtual void onGainedFocus();
//	//virtual void onTextEntered();
//	virtual void onKeyPressed(KeyEvent key);
//	virtual void onKeyReleased(KeyEvent key);
//	virtual void onMouseButtonPressed(MouseButtonEvent mouse);
//	virtual void onMouseButtonReleased(MouseButtonEvent mouse);
//	/*virtual void onMouseWheelMoved();
//	virtual void onMouseMoved();
//	virtual void onMouseEntered();
//	virtual void onMouseLeft();*/
//};
//
