
#pragma once

#include "graphics.h"
#include <string>

#ifndef Player
class Player;
#endif

class IWeapon
{

	public:
		virtual std::string WeaponName() = 0;

		virtual bool LockOnAllowed() = 0;
		virtual bool LockOnRequired() = 0;
		virtual Player* LockOnToPlayer() = 0;
		virtual void LockOnToPlayer(Player* LockedOnTo) = 0;

		virtual void Fire() = 0;
		virtual u32 GetCurrentFireCooldown() = 0;
		virtual u32 GetMaximumFireCooldown() = 0;

		virtual void Update() = 0;
};