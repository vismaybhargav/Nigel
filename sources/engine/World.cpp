#include "World.h"
#include "engine/Body.h"

Engine::World::World() = default;

Engine::World::World(std::initializer_list<Body*> initial_bodies)
    : bodies(initial_bodies)
{
}

void Engine::World::step(double dt)
{
    (void)dt;
    for (Body* body : bodies) {
        body->step(dt);
        
    }
}

void Engine::World::add_body(Body* body)
{
    if (body != nullptr) {
        bodies.push_back(body);
    }
}
