
#pragma once

#include "graphics.h"

class Bullet
{

	private:
		float MinimumThrust;
		float MaximumThrust;
		float TurnSpeed;
		
		void move(irr::core::vector3df vel);
		void rotate(irr::core::vector3df rot);
		void turn(irr::f32 rot);		
		void pitch(irr::f32 rot);
		void roll(irr::f32 rot);

	public:
		// Put this back later
		scene::ISceneNode* Model;
		float CurrentThrust;

		Bullet();

		void Update();

};