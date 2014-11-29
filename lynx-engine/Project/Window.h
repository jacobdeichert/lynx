#pragma once
#include <GL/glew.h>
#include <SFML/Window.hpp>

namespace lynx {
	class Window : public sf::Window {
	public:	
		Window();


		~Window();


		void init(int width, int height, std::string windowName, bool isFullscreen = false);
	protected:
		virtual void onCreate();
	};
}
