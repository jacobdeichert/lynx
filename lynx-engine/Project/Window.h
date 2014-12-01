#pragma once
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "Logger.h"

namespace lynx {
	class Window : public sf::Window {
	public:	
		Window();


		~Window();


		void init(int width, int height, std::string title, bool isFullscreen = false);
	protected:
		bool isFullscreen;
		std::string title;
		virtual void onCreate();
	};
}
