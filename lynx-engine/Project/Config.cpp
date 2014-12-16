#include "Config.h"
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <vector>
#include "FileIO.h"
#include "Logger.h"
using namespace lynx;

/**
 * TODO
 * auto create a default config if one doesn't exist
 */

//================================================================================================
// Private
//================================================================================================
		
namespace {
	rapidjson::Document doc;
	

	/**
	 * Searches the json document for the value of the specified key and returns
	 * true or false based on if it was found.
	 * @param key The key to search for based on this pattern: <Object.*>.key 
	 * @param &valueItr The value of this reference will be set to the member if one 
	 * was found using the specified key.
	 * Example key: "window.size.width" would be broken into 3 parts, separated by periods.
	 * The last value is always the actual key. Prior values are treated as objects
	 * which lead to finding the key.
	 */
	bool getJsonValue(std::string key, rapidjson::Value::MemberIterator &valueItr) {
		std::stringstream ss(key);
		std::string part = "";
		std::vector<std::string> keyParts;

		// Break the key into pieces by the period delimiter.
		while (std::getline(ss, part, '.')) {
			keyParts.push_back(part);
		}

		// Start at the jsonObject at the root level doc.
		rapidjson::Value *jsonObject = &doc;
		// When objectCount reaches the number of keyParts, the key can then be found.
		int objectCount = 0;
		// Loop through all keys in the current jsonObject.
		for (rapidjson::Value::MemberIterator keyMember = jsonObject->MemberBegin(); keyMember != jsonObject->MemberEnd(); ++keyMember) {
			// Check if the current key is the same as the current index in the key parts list.
			// Also check if it's an object like it's supposed to be.
			if (keyMember->name.GetString() == keyParts[objectCount] && keyMember->value.IsObject()) {
				// Set the jsonObject being looped to this new found object.
				jsonObject = &keyMember->value;
				// Reset to just before the first item in the jsonObject (remember that keyMember increments).
				keyMember = jsonObject->MemberBegin() - 1;
				// Update the count since we have just went into one of 
				// the objects specified in the key parts list.
				objectCount++;
			}
			// If the objectCount has reached the final key part, then that
			// is the actual key we are looking for. Now we need its value.
			if (objectCount == keyParts.size() - 1) {
				// Find the value using the last item in the key parts list as the key.
				keyMember = jsonObject->FindMember(keyParts[objectCount].c_str());
				if (keyMember != jsonObject->MemberEnd()) {
					// Return the iterator so that the user can decide
					// what they want to retrieve the value as. (Example valueItr->value.GetInt())
					valueItr = keyMember;
					return true;
				}
			}
		}
		return false;
	}
}

//================================================================================================
// Public
//================================================================================================

void Config::init() {
	FileIO io;
	io.openFileIn("lynx.config");
	std::string json = io.getEntireFile();
	io.closeFileIn();

	// Parse the config file and make sure it was successful.
	if (doc.Parse(json.c_str()).HasParseError()) {
		Log::error("Config || an error occurred while parsing the configuration file \"lynx.config\"");
		Log::error("Config || error: " + std::string(rapidjson::GetParseError_En(doc.GetParseError())));
	} else {
		Log::info("Config || configuration file parsed successfully");
	}
}


std::string Config::getString(std::string key) {
	rapidjson::Value::MemberIterator itr;
	
	if (getJsonValue(key, itr) && itr->value.IsString()) {
		return itr->value.GetString();
	}

	return "";
}


int Config::getInt(std::string key) {
	rapidjson::Value::MemberIterator itr;

	if (getJsonValue(key, itr) && itr->value.IsInt()) {
		return itr->value.GetInt();
	}

	return NULL;
}


float Config::getFloat(std::string key) {
	rapidjson::Value::MemberIterator itr;

	if (getJsonValue(key, itr) && itr->value.IsDouble()) {
		return (float)itr->value.GetDouble();
	}

	return NULL;
}


double Config::getDouble(std::string key) {
	rapidjson::Value::MemberIterator itr;

	if (getJsonValue(key, itr) && itr->value.IsDouble()) {
		return itr->value.GetDouble();
	}

	return NULL;
}


bool Config::getBool(std::string key) {
	rapidjson::Value::MemberIterator itr;

	if (getJsonValue(key, itr) && itr->value.IsBool()) {
		return itr->value.GetBool();
	}

	return NULL;
}
