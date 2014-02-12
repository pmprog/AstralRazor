
#pragma once

#include "graphics.h"

#ifndef IWeapon
class IWeapon;
#endif

class Player
{

	private:
		//scene::ISceneNode* Model;
		scene::ICameraSceneNode *Cam;
		float CurrentThrust;
		float MinimumThrust;
		float MaximumThrust;
		float TurnSpeed;
		
		void makeCockpit(irr::core::vector3df offset);
		void move(irr::core::vector3df vel);
		void rotate(irr::core::vector3df rot);
		void turn(irr::f32 rot);		
		void pitch(irr::f32 rot);
		void roll(irr::f32 rot);

		IWeapon* leftWeapon;
		IWeapon* rightWeapon;

	public:
		// Put this back later
		scene::ISceneNode* Model;

		int Control_Thrust;
		int Control_Pitch;
		int Control_Roll;

		Player();

		void SetCamera(scene::ICameraSceneNode *Camera);
		void Update();

};