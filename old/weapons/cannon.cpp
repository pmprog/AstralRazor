
#include "cannon.h"
#include "../engine.h"
#include "../player.h"
#include "../bullet.h"

Cannon::Cannon()
{
	Cooldown = 0;
}

std::string Cannon::WeaponName()
{
	return "Cannon";
}

bool Cannon::LockOnAllowed()
{
	return false;
}

bool Cannon::LockOnRequired()
{
	return false;
}

Player* Cannon::LockOnToPlayer()
{
	return 0;
}
void Cannon::LockOnToPlayer(Player* LockedOnTo)
{
}

void Cannon::Fire()
{
	if( Cooldown == 0 )
	{
		// TODO: Fire
		Bullet* x = new Bullet();
		x->Model->setPosition( Engine::Instance->ply->Model->getPosition() );
		x->Model->setRotation( Engine::Instance->ply->Model->getRotation() );
		Engine::Instance->blt.push_back( x );
	}
}

u32 Cannon::GetCurrentFireCooldown()
{
	return Cooldown;
}

u32 Cannon::GetMaximumFireCooldown()
{
	return 300;
}

void Cannon::Update()
{
	if( Cooldown > 0 )
	{
		Cooldown--;
	}
}
