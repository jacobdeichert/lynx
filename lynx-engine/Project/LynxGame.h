#pragma once
// TODO: get rid of printf statements and log to my logmanager instead.
#include <iostream>
#include "Window.h"

namespace lynx {
	using KeyEvent = sf::Event::KeyEvent;
	class LynxGame {
	public:
		LynxGame();


		virtual ~LynxGame();


		void setup(int windowWidth, int windowHeight, std::string windowName, bool isFullscreen = false);
		void shutdown();


		virtual void init() = 0;
		virtual void render() = 0;
		virtual void update() = 0;

		virtual void onClose() {}							///< The window requested to be closed (no data)
		virtual void onResize(int width, int height) {}		///< The window was resized (data in event.size)
		virtual void onLostFocus() {}						///< The window lost the focus (no data)
		virtual void onGainedFocus() {}						///< The window gained the focus (no data)
		virtual void onTextEntered() {}						///< A character was entered (data in event.text)
		virtual void onKeyPressed(KeyEvent key) {}			///< A key was pressed (data in event.key)
		virtual void onKeyReleased(KeyEvent key) {}			///< A key was released (data in event.key)
		virtual void onMouseWheelMoved() {}					///< The mouse wheel was scrolled (data in event.mouseWheel)
		virtual void onMouseButtonPressed() {}				///< A mouse button was pressed (data in event.mouseButton)
		virtual void onMouseButtonReleased() {}				///< A mouse button was released (data in event.mouseButton)
		virtual void onMouseMoved() {}						///< The mouse cursor moved (data in event.mouseMove)
		virtual void onMouseEntered() {}					///< The mouse cursor entered the area of the window (no data)
		virtual void onMouseLeft() {}						///< The mouse cursor left the area of the window (no data)
		virtual void onJoystickButtonPressed() {}			///< A joystick button was pressed (data in event.joystickButton)
		virtual void onJoystickButtonReleased() {}			///< A joystick button was released (data in event.joystickButton)
		virtual void onJoystickMoved() {}					///< The joystick moved along an axis (data in event.joystickMove)
		virtual void onJoystickConnected() {}				///< A joystick was connected (data in event.joystickConnect)
		virtual void onJoystickDisconnected() {}			///< A joystick was disconnected (data in event.joystickConnect)
	private:
		Window window;
		bool hasShutdown;
		void beginLoop();
	};
}
