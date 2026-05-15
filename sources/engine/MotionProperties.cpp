#include "MotionProperties.h"
#include "raylib.h"

Engine::MotionProperties::MotionProperties(
    Vector3 initial_position,
    Vector3 initial_velocity,
    Vector3 initial_acceleration
) : position(initial_position), velocity(initial_velocity), acceleration(initial_acceleration) {}
