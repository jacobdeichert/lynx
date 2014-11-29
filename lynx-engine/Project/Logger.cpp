#include "Logger.h"

namespace lynx {

const char* Logger::SEVERITY_LEVEL_NAME[4] = { "", "ERROR", "WARN", "INFO" };



Logger::Logger(std::string filePath, SeverityLevel level) {
	// Set the settings.
	logFilePath = filePath;
	severityLevel = level;

	// Make sure to close the current log file if it's open.
	if (io.isOutOpen()) io.closeFileOut();

	// Open a new file for the logger.
	io.openFileOut(logFilePath);
}



Logger::~Logger() {
	// Make sure to close the current log file if it's open.
	if (io.isOutOpen()) io.closeFileOut();
}



void Logger::log(std::string message, SeverityLevel level) {
	if (level != SEV_LEVEL_NONE && level <= severityLevel) {
		io.writel(SEVERITY_LEVEL_NAME[level] + std::string(": ") + message);
	}
}



void Logger::warn(std::string message) {
	log(message, SEV_LEVEL_WARN);
}



void Logger::error(std::string message) {
	log(message, SEV_LEVEL_ERROR);
}
}
