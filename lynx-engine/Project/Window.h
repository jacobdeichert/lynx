#pragma once
#include <SFML/Window.hpp>



namespace lynx {
	class Window : public sf::Window {
	public:	
		Window();


		~Window();


		void init();
	protected:
		bool isFullscreen;
		std::string title;
		virtual void onCreate();
	};
}
