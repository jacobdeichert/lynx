//#include "worlds/test/TestWorld.h"
#include "worlds/particle-system/ParticleSystemWorld.h"
//#include "worlds/maze/MazeWorld.h"

int main() {
	//TestWorld *world = new TestWorld();
	ParticleSystemWorld *world = new ParticleSystemWorld();
	//MazeWorld *world = new MazeWorld();
	delete world;
}
