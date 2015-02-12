#pragma once
#include <Windows.h> // should be lowercase w?

namespace GameEngine {
	/**
	* The Clock allows the application to count hardware ticks and convert
	* them to current time in seconds or milliseconds.
	*/
	class Clock {
	public:
		/**
		* Returns a pointer to this instance.
		* @return An instance of LogManager.
		*/
		static Clock* getInstance();

		
		/**
		* Calculates the elapsed time in seconds.
		* @return The elapsed time in seconds.
		*/
		double getCurrentTimeSeconds();


		/** 
		* Calculates the elapsed time in milliseconds.
		* @return The elapsed time in milliseconds.
		*/
		double getCurrentTimeMilliseconds();


		/**
		* Returns the ticks per second.
		* @return The ticks per second.
		*/
		LARGE_INTEGER getTicksPerSecond();


		/**
		* The clock is ready if the hardware supports the high resolution timer.
		* @return True if the hardware supports the high resolution timer.
		*/
		bool isReady();
	private:
		/**
		* The one and only instance of Clock.
		*/
		static Clock* instance;


		/**
		* Start of the counter which is used to calculate the current time.
		*/
		LARGE_INTEGER counterStart;


		/**
		* The current counter value which is used to calculate the current time.
		*/
		LARGE_INTEGER counterCurrent;


		/**
		* The number of ticks per second.
		*/
		LARGE_INTEGER ticksPerSecond;


		/**
		* This defines whether or not the hardware supports the high resolution timer.
		*/
		bool isHighResSupported;


		/**
		* Private constructor and destructor to ensure this remains a singleton.
		* The constructor is called when getInstance() is called for the first time.
		* It initializes the clock and checks if the high resolution timer is supported.
		*/
		Clock();
		~Clock();
	};

}
