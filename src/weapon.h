
#pragma once

#include "graphics.h"
#include <string>

#ifndef Body
class Body;
#endif

#ifndef Craft
class Craft;
#endif

class Weapon
{

	protected:
		Craft* owner;

		Craft* lockOnTarget;

		u32 cooldownPerShot;
		u32 cooldownCurrent;

		u32 heatGeneratedPerShot;
		u32 heatShutdownLimit;
		u32 heatDissipateRate;
		u32 heatReengage;
		u32 heatCurrent;
		bool heatShutDown;

	public:
		Weapon( Craft* Owner );

		bool LockOnAllowed();
		bool LockOnRequired();
		Craft* LockOnPlayer();
		void LockOnToPlayer(Craft* LockedOnTo);

		u32 CooldownMax();
		u32 CooldownCurrent();

		u32 HeatMax();
		u32 HeatCurrent();
		u32 HeatEngage();

		void Fire();
		void Update();

		virtual std::string WeaponName();
		virtual Body* SpawnBullet();

};