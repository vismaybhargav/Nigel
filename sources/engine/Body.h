#ifndef BODY_H
#define BODY_H

#include "engine/MotionProperties.h"
#include "raylib.h"
#include <vector>

namespace Engine {

struct AppliedForce {
	Vector3 force_N;
	float remaining_time_s;
};

class Body {
	public:
		double mass_kg;
		MotionProperties motion_properties;
		Vector3 total_force;
		std::vector<AppliedForce> active_forces;
		
		Body(
			double mass_kg,
			Vector3 initial_position,
			Vector3 initial_velocity,
			Vector3 initial_acceleration,
			Vector3 total_force
		);

		Body(
			double mass_kg
		);

		Body(
		);

		void add_force(Vector3 force_N);
		void add_force(Vector3 force_N, double duration_s);
		void add_gravity();
		void step(double dt);

	private:
		void update_total_force();
	};
}
#endif // BODY_H
