
#pragma once

#include "../iweapon.h"

class MissileLauncher : public IWeapon
{
	private:
		Player* LockTarget;
		u32 Cooldown;

	public:
		MissileLauncher();

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