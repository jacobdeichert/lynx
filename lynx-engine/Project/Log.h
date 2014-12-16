#pragma once
#include <map>

namespace lynx {
	/**
	 * Logger allows the application to write messages to a specified log file. It can be configured to
	 * print messages greater than or equal to a specific severity level.
	 *
	 * This is a special global + anonymous namespace. This is better than a static class layout
	 * apparently. Basically, the first anonymous namespace holds global variables that no one can
	 * access except the Log namespace below. This is safer than having private variables in a class
	 * full of static methods I guess.
	 * http://stackoverflow.com/questions/9321/how-do-you-create-a-static-class-in-c
	 */
	namespace Log {
		/**
		 * The possible levels of severity for the output of messages to the log file.
		 * Everything less than the specified severity will be written to the log file.
		 */
		enum SeverityLevel {
			SEV_LEVEL_TRACE,
			SEV_LEVEL_DEBUG,
			SEV_LEVEL_FATAL,
			SEV_LEVEL_ERROR,
			SEV_LEVEL_WARN,
			SEV_LEVEL_INFO
		};


		/**
		 * Optionally set severity level of the output.
		 * @param level The level of severity that will define which messages are sent to the log file.
		 */
		void init(SeverityLevel level = SEV_LEVEL_INFO);
		
		
		/**
		 * Deinitialize by closing any open files.
		 */
		void deinit();
		
		
		/**
		 * Write to the log file with a severity level of SEV_LEVEL_TRACE.
		 * @param message The message to be written to the log file
		 */
		void trace(std::string message);


		/**
		 * Write to the log file with a severity level of SEV_LEVEL_DEBUG.
		 * @param message The message to be written to the log file
		 */
		void debug(std::string message);


		/**
		 * Write to the log file with a severity level of SEV_LEVEL_FATAL.
		 * @param message The message to be written to the log file
		 */
		void fatal(std::string message);



		/**
		 * Write to the log file with a severity level of SEV_LEVEL_ERROR.
		 * @param message The message to be written to the log file
		 */
		void error(std::string message);


		/**
		 * Write to the log file with a severity level of SEV_LEVEL_WARN.
		 * @param message The message to be written to the log file
		 */
		void warn(std::string message);


		/**
		 * Write to the log file with a severity level of SEV_LEVEL_INFO.
		 * @param message The message to be written to the log file
		 */
		void info(std::string message);
	}
}
