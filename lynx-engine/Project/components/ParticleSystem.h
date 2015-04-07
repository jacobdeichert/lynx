#pragma once
#include "Component.h"
#include <glm.hpp>

namespace lynx {
	class ParticleSystem : public Component {
	public:
		/**
		 * Creates a particle system with a single color.
		 * @param gameObject The game object that this component belongs to.
		 * @param numParticles The number of particles that will be generated.
		 * @param isRandom Determines whether random colors should be used for each particle.
		 *		The default value is false. If the value is true, any specified color is ignored.
		 * @param color The color of every particle in RGB (0-1). The default value is white.
		 */
		ParticleSystem(GameObject *gameObject, int numParticles, bool isRandom = false, glm::vec3 color = glm::vec3(1, 1, 1));


		virtual ~ParticleSystem();


		virtual void update();
	};
}

