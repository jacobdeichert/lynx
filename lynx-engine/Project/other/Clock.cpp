#include "Clock.h"
using namespace GameEngine;



Clock* Clock::instance = nullptr;



Clock::Clock() {
	// commenting for now because it gives a warning
	//isHighResSupported = QueryPerformanceFrequency(&ticksPerSecond);
	//QueryPerformanceCounter(&counterStart);
}



Clock::~Clock() {}



Clock* Clock::getInstance() {
	if (instance == nullptr) {
		instance = new Clock();
	}
	return instance;
}



double Clock::getCurrentTimeSeconds() {
	QueryPerformanceCounter(&counterCurrent);
	return ((double)counterCurrent.QuadPart - (double)counterStart.QuadPart) / (double)ticksPerSecond.QuadPart;
}



double Clock::getCurrentTimeMilliseconds() {
	return getCurrentTimeSeconds() * 1000;
}



LARGE_INTEGER Clock::getTicksPerSecond() {
	return ticksPerSecond;
}


bool Clock::isReady() {
	return isHighResSupported;
}