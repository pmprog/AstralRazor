
#pragma once

#include "body.h"

#ifndef Weapon
class Weapon;
#endif

class Craft : public Body
{

	private:
		scene::ICameraSceneNode *Cam;
		void makeCockpit(irr::core::vector3df offset);
		bool Controlled;

		f32 MaximumThrust;
		f32 MinimumThrust;
		f32 TurnSpeed;
		f32 Acceleration;
		f32 Deceleration;

	public:
		Weapon* LeftWeapon;
		Weapon* RightWeapon;

		Craft( core::vector3df Position, core::vector3df Rotation );
		void SetCamera(scene::ICameraSceneNode *Camera);

		virtual void Update();

};