#pragma once
#include <string>

namespace lynx {
	namespace Config {

		
		void init();


		std::string getString(std::string key);


		int getInt(std::string key);


		float getFloat(std::string key);
	}
}
