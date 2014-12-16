#pragma once
#include <string>

namespace lynx {
	/**
	 * Config allows the application to read values from a configuration file using specified keys.
	 * The configuration file is a json formatted text file named "lynx.config". Config uses the 
	 * rapidjson header-only library to parse the json config file.
	 *
	 * This is a special global + anonymous namespace. This is better than a static class layout
	 * apparently. Basically, the first anonymous namespace holds global variables that no one can
	 * access except the Log namespace below. This is safer than having private variables in a class
	 * full of static methods I guess.
	 * http://stackoverflow.com/questions/9321/how-do-you-create-a-static-class-in-c
	 */
	namespace Config {

		/**
		 * Initialize Config. Should be initialized as soon as possible.
		 */
		void init();


		/**
		 * Get the value of the specified key as a string.
		 * @param key The key to search for based on this pattern: <Object.*>.key
		 */
		std::string getString(std::string key);


		/**
		 * Get the value of the specified key as an integer.
		 * @param key The key to search for based on this pattern: <Object.*>.key
		 */
		int getInt(std::string key);


		/**
		 * Get the value of the specified key as a float.
		 * @param key The key to search for based on this pattern: <Object.*>.key
		 */
		float getFloat(std::string key);


		/**
		 * Get the value of the specified key as a double.
		 * @param key The key to search for based on this pattern: <Object.*>.key
		 */
		double getDouble(std::string key);


		/**
		 * Get the value of the specified key as a boolean. 
		 * @param key The key to search for based on this pattern: <Object.*>.key
		 */
		bool getBool(std::string key);
	}
}
