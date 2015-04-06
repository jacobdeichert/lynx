#pragma once
#include "GameObject.h"

namespace lynx {
	/**
	* This is a special global + anonymous namespace. This is better than a static class layout
	* apparently. Basically, the first anonymous namespace holds global variables that no one can
	* access except the Log namespace below. This is safer than having private variables in a class
	* full of static methods I guess.
	* http://stackoverflow.com/questions/9321/how-do-you-create-a-static-class-in-c
	*/
	namespace ParticleSystemFactory {
		/**
		 * Creates a particle system with a single color.
		 * @param name The name of the game object as well as its mesh ID.
		 * @param numParticles The number of particles that will be generated.
		 * @param isRandom Determines whether random colors should be used for each particle. 
		 *		The default value is false. If the value is true, any specified color is ignored.
		 * @param color The color of every particle in RGB (0-1). The default value is white.
		 */
		GameObject* create(std::string name, int numParticles, bool isRandom = false, glm::vec3 color = glm::vec3(1, 1, 1));
	}
}
