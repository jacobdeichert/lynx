#pragma once
#include "FileIO.h"

namespace lynx {
/**
* The Logger allows the application to write messages to a specified log
* file. It can be configured to print messages greater than or equal to a specific
* severity level.
*/
class Logger {
public:
	/*
		The possible levels of severity for the output of messages to the log file.
		Everything less than the specified severity will be written to the log file.
	*/
	enum SeverityLevel {
		SEV_LEVEL_NONE,
		SEV_LEVEL_ERROR,
		SEV_LEVEL_WARN,
		SEV_LEVEL_INFO
	};


	/*
		Set the path for the log file and the severity level of the output.
		@param filePath The path to the log file.
		@param level The level of severity that will define which messages are sent to the log file.
	*/
	Logger(std::string filePath, SeverityLevel level = SEV_LEVEL_INFO);



	~Logger();



	/*
		Write to the log file with a given severity level. The default severity level
		is SEV_LEVEL_INFO if none is specified.
		@param message The message to be written to the log file
		@param level The level of severity for this message
	*/
	void log(std::string message, SeverityLevel level = SEV_LEVEL_INFO);


	/*
		Write to the log file with a severity level of SEV_LEVEL_WARN.
		@param message The message to be written to the log file
	*/
	void warn(std::string message);


	/*
		Write to the log file with a severity level of SEV_LEVEL_ERROR.
		@param message The message to be written to the log file
	*/
	void error(std::string message);
private:
	/*
		FileIO is used to write to a log file based on logFilePath.
	*/
	FileIO io;


	/*
		The path to the log file.
	*/
	std::string logFilePath;


	/*
		The current level of severity used to define which log messages
		are sent to the log file.
	*/
	SeverityLevel severityLevel;


	/*
		Strings that represent each severity level. They are defined in Logger.cpp.
	*/
	static const char* SEVERITY_LEVEL_NAME[];
};
}
