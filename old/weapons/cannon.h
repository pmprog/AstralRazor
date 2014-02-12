
#pragma once

#include "../iweapon.h"

class Cannon : public IWeapon
{
	private:
		u32 Cooldown;

	public:
		Cannon();

		virtual std::string WeaponName();

		virtual bool LockOnAllowed();
		virtual bool LockOnRequired();
		virtual Player* LockOnToPlayer();
		virtual void LockOnToPlayer(Player* LockedOnTo);

		virtual void Fire();
		virtual u32 GetCurrentFireCooldown();
		virtual u32 GetMaximumFireCooldown();

		virtual void Update();
};