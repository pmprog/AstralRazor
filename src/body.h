
#pragma once

#include "graphics.h"

class Body
{

	protected:
		scene::ISceneNode* Model;
		f32 CurrentThrust;

		void move(irr::core::vector3df vel);
		void rotate(irr::core::vector3df rot);
		void turn(irr::f32 rot);		
		void pitch(irr::f32 rot);
		void roll(irr::f32 rot);

	public:

		Body( scene::IAnimatedMesh* Mesh, core::vector3df Position, core::vector3df Rotation );
		~Body();

		core::vector3df GetPosition();
		core::vector3df GetRotation();

		f32 GetThrust();
		void SetThrust(f32 Thrust);
		
		virtual void Update();

};