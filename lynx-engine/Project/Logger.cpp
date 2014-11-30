#include "Logger.h"
using namespace lynx;

std::map<std::string, Logger*> Logger::loggers;

const char* Logger::SEVERITY_LEVEL_NAME[3] = { "ERROR", "WARN", "" };



Logger::Logger(std::string filename, SeverityLevel level) {
	// Set the settings.
	logFilePath = filename + ".log";
	severityLevel = level;

	// Make sure to close the current log file if it's open.
	if (io.isOutOpen()) io.closeFileOut();

	// Open a new file for the logger.
	io.openFileOut(logFilePath);
}


Logger::~Logger() {
	// Make sure to close the current log file if it's open.
	if (io.isOutOpen()) io.closeFileOut();

	// TODO: Delete all loggers.

}


Logger& Logger::get(std::string filename, SeverityLevel level) {
	// If the logger doesn't exist, create it.
	if (loggers.find(filename) == loggers.end()) {
		loggers[filename] = new Logger(filename, level);
	}
	loggers[filename]->severityLevel = level;
	return *loggers[filename];
}


void Logger::log(std::string message, SeverityLevel level) {
	if (level <= severityLevel) {
		io.writel(SEVERITY_LEVEL_NAME[level] + std::string("> ") + message);
	}
}


void Logger::warn(std::string message) {
	log(message, SEV_LEVEL_WARN);
}


void Logger::error(std::string message) {
	log(message, SEV_LEVEL_ERROR);
}
