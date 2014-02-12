
#include "missile.h"

MissileLauncher::MissileLauncher()
{
	Cooldown = 0;
	LockTarget = 0;
}

std::string MissileLauncher::WeaponName()
{
	return "MissileLauncher";
}

bool MissileLauncher::LockOnAllowed()
{
	return true;
}

bool MissileLauncher::LockOnRequired()
{
	return false;
}

Player* MissileLauncher::LockOnToPlayer()
{
	return LockTarget;
}
void MissileLauncher::LockOnToPlayer(Player* LockedOnTo)
{
	LockTarget = LockedOnTo;
}

void MissileLauncher::Fire()
{
	if( Cooldown == 0 )
	{
		// TODO: Fire
	}
}

u32 MissileLauncher::GetCurrentFireCooldown()
{
	return Cooldown;
}

u32 MissileLauncher::GetMaximumFireCooldown()
{
	return 3000;
}

void MissileLauncher::Update()
{
	if( Cooldown > 0 )
	{
		Cooldown--;
	}
}
