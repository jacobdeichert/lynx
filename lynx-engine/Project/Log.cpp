#include "Log.h"
#include "FileIO.h"
using namespace lynx;

//================================================================================================
// Private
//================================================================================================

namespace {
	/**
	 * Strings that represent each severity level. They are defined in Logger.cpp.
	 */
	const char* SEVERITY_LEVEL_NAME[6] = { "TRACE", "DEBUG", "FATAL", "ERROR", "WARN", "INFO" };


	/**
	 * The current level of severity used to define which log messages
	 * are sent to the log file.
	 */
	Log::SeverityLevel severityLevel;


	/**
	 * FileIO is used to write to a log file based on logFilePath.
	 */
	FileIO io;


	/**
	 * The path to the log file.
	 */
	std::string logFilePath = "lynx.log";

			
	/**
	 * Write to the log file with a given severity level.
	 * @param message The message to be written to the log file
	 * @param level The level of severity for this message
	 */
	void write(std::string message, Log::SeverityLevel level) {
		if (level <= severityLevel) {
			io.writeLine(SEVERITY_LEVEL_NAME[level] + std::string("> ") + message);
		}
	}
}

//================================================================================================
// Public
//================================================================================================

void Log::init(SeverityLevel level) {
	// Make sure to close the current log file if it's open.
	if (io.isOutOpen()) io.closeFileOut();

	// Set the severity level.
	severityLevel = level;

	// Open a new file for the logger.
	io.openFileOut(logFilePath);

	Log::info("Log || logger initialized");
}


void Log::deinit() {
	Log::info("Log || logger deinitialized");

	// Make sure to close the current log file if it's open.
	if (io.isOutOpen()) io.closeFileOut();
}


void Log::trace(std::string message) {
	write(message, SEV_LEVEL_TRACE);
}


void Log::debug(std::string message) {
	write(message, SEV_LEVEL_DEBUG);
}


void Log::fatal(std::string message) {
	write(message, SEV_LEVEL_FATAL);
}


void Log::error(std::string message) {
	write(message, SEV_LEVEL_ERROR);
}


void Log::warn(std::string message) {
	write(message, SEV_LEVEL_WARN);
}


void Log::info(std::string message) {
	write(message, SEV_LEVEL_INFO);
}
