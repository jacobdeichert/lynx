#include "LogManager.h"
using namespace lynx;

LogManager* LogManager::instance = nullptr;
const char* LogManager::SEVERITY_LEVEL_NAME[4] = { "", "ERROR", "WARN", "INFO" };

LogManager::LogManager() {
	reset("LogManager.log", SEV_LEVEL_INFO);
}



LogManager::~LogManager() {
    // Make sure to close the current log file if it's open.
	if (io.isOutOpen()) io.closeFileOut();
	delete instance;
}



LogManager* LogManager::getInstance() {
	if (instance == nullptr) {
		instance = new LogManager();
	}
	return instance;
}



void LogManager::log(std::string message, SeverityLevel level) {
	if (level != SEV_LEVEL_NONE && level <= severityLevel) {
		io.writel(SEVERITY_LEVEL_NAME[level] + std::string(": ") + message);
	}
}



void LogManager::warn(std::string message) {
	log(message, SEV_LEVEL_WARN);
}



void LogManager::error(std::string message) {
	log(message, SEV_LEVEL_ERROR);
}



void LogManager::reset(std::string filename, SeverityLevel level) {
	// Set the settings.
	logFilePath = filename;
	severityLevel = level;

	// Make sure to close the current log file if it's open.
	if (io.isOutOpen()) io.closeFileOut();

	// Open a new file for the logger.
	io.openFileOut(logFilePath);
}

