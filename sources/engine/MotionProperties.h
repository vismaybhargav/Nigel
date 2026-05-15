#ifndef MOTION_PROPERTIES_H
#define MOTION_PROPERTIES_H

#include "raylib.h"
namespace Engine {

class MotionProperties {
	public:
		Vector3 position;
		Vector3 velocity;
		Vector3 acceleration;

	MotionProperties(
		Vector3 initial_position,
		Vector3 initial_velocity,
		Vector3 initial_acceleration
	);
};

}

#endif // MOTION_PROPERTIES_H
