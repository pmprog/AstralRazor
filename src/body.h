
#pragma once

#include "graphics.h"

class Body
{

	protected:
		scene::ISceneNode* Model;
		float CurrentThrust;

		void move(irr::core::vector3df vel);
		void rotate(irr::core::vector3df rot);
		void turn(irr::f32 rot);		
		void pitch(irr::f32 rot);
		void roll(irr::f32 rot);

		virtual void setModel();

	public:

		Body( core::vector3df Position, core::vector3df Rotation );
		~Body();

		
		virtual void Update();

};