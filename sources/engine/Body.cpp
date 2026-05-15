#include "Body.h"
#include "engine/MotionProperties.h"
#include "raylib.h"
#include "raymath.h"

Engine::Body::Body(
    double mass_kg, 
	Vector3 initial_position,
	Vector3 initial_velocity,
	Vector3 initial_acceleration,
    Vector3 initial_force
) : mass_kg(mass_kg), 
    motion_properties(
        initial_position,
        initial_velocity,
        initial_acceleration
    ),
    total_force((Vector3) {0.f, 0.f, 0.f}),
    active_forces()
{
    !Vector3Equals(initial_force, Vector3Zero()) ? add_force(initial_force) : update_total_force();
}

Engine::Body::Body(
    double mass_kg
) : mass_kg(mass_kg),
    motion_properties(
        (Vector3) {0.f, 0.f, 0.f},
        (Vector3) {0.f, 0.f, 0.f},
        (Vector3) {0.f, 0.f, 0.f}
    ),
    total_force((Vector3) {0.f, 0.f, 0.f}),
    active_forces()
{
}

void Engine::Body::add_force(Vector3 force_N) {
    active_forces.push_back({force_N, -1.0f});
    update_total_force();
}

void Engine::Body::add_force(Vector3 force_N, double duration_s) {
    active_forces.push_back({force_N, static_cast<float>(duration_s)});
    update_total_force();
}

void Engine::Body::add_gravity() {
    add_force((Vector3){0.f, -9.81f * (float)mass_kg, 0.f});
}

void Engine::Body::step(double dt) {
    const float dt_seconds = static_cast<float>(dt);

    for (auto it = active_forces.begin(); it != active_forces.end();) {
        if (it->remaining_time_s >= 0.0f) {
            it->remaining_time_s -= dt_seconds;
            if (it->remaining_time_s <= 0.0f) {
                it = active_forces.erase(it);
                continue;
            }
        }
        ++it;
    }

    update_total_force();

    motion_properties.velocity = 
        Vector3Add(
            motion_properties.velocity,
            Vector3Scale(motion_properties.acceleration, dt_seconds)
        );
    motion_properties.position = 
        Vector3Add(
            motion_properties.position,
            Vector3Scale(motion_properties.velocity, dt_seconds)
        );
}

void Engine::Body::update_total_force() {
    total_force = Vector3Zero();

    for (const AppliedForce& applied_force : active_forces) {
        total_force = Vector3Add(total_force, applied_force.force_N);
    }

    motion_properties.acceleration = Vector3Scale(
        total_force,
        1.0f / static_cast<float>(mass_kg)
    );
}
