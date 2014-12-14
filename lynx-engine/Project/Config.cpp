#include "Config.h"
#include <rapidjson\document.h>
#include "FileIO.h"
//#include "Logger.h"



namespace lynx {
	namespace Config {
		//================================================================================================
		// Private
		//================================================================================================
		
		namespace {
			rapidjson::Document doc;
			
		}

		//================================================================================================
		// Public
		//================================================================================================

		void init() {
			FileIO io;
			io.openFileIn("lynxconfig.json");
			std::string json = io.getEntireFile();
			io.closeFileIn();
			printf("%s", json.c_str());
		}




	}
}







