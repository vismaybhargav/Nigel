#ifndef WORLD_H
#define WORLD_H

#include "engine/Body.h"
#include <initializer_list>
#include <vector>

namespace Engine {

class World {
public:
	std::vector<Body*> bodies;

	World();
	World(std::initializer_list<Body*> initial_bodies);

	void step(double dt);

	void add_body(Body* body);
};

}

#endif // WORLD_H
