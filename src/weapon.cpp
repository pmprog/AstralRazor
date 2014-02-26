
#include "weapon.h"
#include "engine.h"
#include "body.h"
#include "craft.h"

Weapon::Weapon( Craft* Owner )
{
	owner = Owner;
	lockOnTarget = 0;

	cooldownPerShot = 10;
	cooldownCurrent = 0;

	heatGeneratedPerShot = 10;
	heatShutdownLimit = 300;
	heatDissipateRate = 8;
	heatReengage = 260;
	heatCurrent = 0;
	heatShutDown = false;
}

bool Weapon::LockOnAllowed()
{
	return false;
}

bool Weapon::LockOnRequired()
{
	return false;
}

Craft* Weapon::LockOnPlayer()
{
	return lockOnTarget;
}

void Weapon::LockOnToPlayer(Craft* LockedOnTo)
{
	lockOnTarget = LockedOnTo;
}

u32 Weapon::CooldownMax()
{
	return cooldownPerShot;
}

u32 Weapon::CooldownCurrent()
{
	return cooldownCurrent;
}

u32 Weapon::HeatMax()
{
	return heatShutdownLimit;
}

u32 Weapon::HeatCurrent()
{
	return heatCurrent;
}

u32 Weapon::HeatEngage()
{
	return heatReengage;
}

void Weapon::Fire()
{
	if( cooldownCurrent > 0 || heatShutDown )
	{
		return;
	}
	SpawnBullet();
	cooldownCurrent = cooldownPerShot;
	heatCurrent += heatDissipateRate;
	if( heatCurrent >= heatShutdownLimit )
	{
		heatShutdownLimit = heatShutdownLimit;
		heatShutDown = true;
	}
}

void Weapon::Update()
{
	if( cooldownCurrent > 0 )
	{
		cooldownCurrent--;
	}
	if( heatCurrent > 0 )
	{
		heatCurrent -= heatDissipateRate;
		if( heatCurrent < 0 )
		{
			heatCurrent = 0;
		}
	}
	if( heatShutDown && heatCurrent <= heatReengage )
	{
		heatShutDown = false;
	}
}

std::string Weapon::WeaponName()
{
	return "Core Weapon";
}

Body* Weapon::SpawnBullet()
{
	Body* b = new Body( Engine::Instance->LoadMeshFile("resource/bullet.obj"), owner->GetPosition(), owner->GetRotation() );
	b->SetThrust( 80.0 );
	b->Update();
	Engine::Instance->AddBody( b );
	return b;
}