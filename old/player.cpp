
#include "player.h"
#include "engine.h"
#include "weapons/cannon.h"
#include "weapons/missile.h"

Player::Player()
{
	Cam = 0;

	Control_Thrust = 0;
	Control_Pitch = 0;
	Control_Roll = 0;

	CurrentThrust = 1.5f;
	MinimumThrust = 0.0f;
	MaximumThrust = 8.0f;
	TurnSpeed = 1.5f;

	//scene::IAnimatedMesh fighterMesh = ;
	Model = Engine::Instance->GetSceneManager()->addAnimatedMeshSceneNode( Engine::Instance->GetSceneManager()->getMesh("resource/X-17 Viper flying.obj") );  // addCubeSceneNode();
	Model->setMaterialFlag( video::EMF_LIGHTING, false );
	Model->setScale( core::vector3df(0.1f) );

	leftWeapon = new Cannon();
	rightWeapon = new MissileLauncher();
}

// free flight functions
void Player::makeCockpit(irr::core::vector3df offset)
{
	irr::core::matrix4 m;
	m.setRotationDegrees(Model->getRotation());

	irr::core::vector3df frv = irr::core::vector3df (0.0f, 0.0f, 1.0f);
	m.transformVect(frv);

	irr::core::vector3df upv = irr::core::vector3df (0.0f, 1.0f, 0.0f);
	m.transformVect(upv);

	m.transformVect(offset);

	offset += Model->getPosition();
	Cam->setPosition(offset);

	Cam->setUpVector(upv);

	offset += frv;
	Cam->setTarget(offset);

	Cam->updateAbsolutePosition();
}

void Player::move(irr::core::vector3df vel)
{
	irr::core::matrix4 m;
	m.setRotationDegrees(Model->getRotation());
	m.transformVect(vel);
	Model->setPosition(Model->getPosition() + vel);
	Model->updateAbsolutePosition();
}

void Player::rotate(irr::core::vector3df rot)
{
	irr::core::matrix4 m;
	m.setRotationDegrees(Model->getRotation());
	irr::core::matrix4 n;
	n.setRotationDegrees(rot);
	m *= n;
	Model->setRotation( m.getRotationDegrees() );
	Model->updateAbsolutePosition();
}

void Player::turn(irr::f32 rot)
{
	rotate(irr::core::vector3df(0.0f, rot, 0.0f) );
}

void Player::pitch(irr::f32 rot)
{
	rotate(irr::core::vector3df(rot, 0.0f, 0.0f) );
}

void Player::roll(irr::f32 rot)
{
	rotate(irr::core::vector3df(0.0f, 0.0f, rot) );
}

void Player::SetCamera(scene::ICameraSceneNode *Camera)
{
	Cam = Camera;
}

void Player::Update()
{
	move( core::vector3df( 0, 0, CurrentThrust ) );
	if( Cam != 0 )
	{
		makeCockpit( core::vector3df( 0.0f, 24.0f, -60.0f ) );
	}

	if( Engine::Instance->GetKeyState(irr::KEY_UP) )
	{
		pitch(TurnSpeed);
	}
	if( Engine::Instance->GetKeyState(irr::KEY_DOWN) )
	{
		pitch(-TurnSpeed);
	}
	if( Engine::Instance->GetKeyState(irr::KEY_LEFT) )
	{
		roll(TurnSpeed);
	}
	if( Engine::Instance->GetKeyState(irr::KEY_RIGHT) )
	{
		roll(-TurnSpeed);
	}
	if( Engine::Instance->GetKeyState(irr::KEY_KEY_W) || Engine::Instance->GetKeyState(irr::KEY_RCONTROL) || Engine::Instance->GetKeyState(irr::KEY_PRIOR) )
	{
		CurrentThrust += 0.2f;
		if( CurrentThrust > MaximumThrust )
		{
			CurrentThrust = MaximumThrust;
		}
	}
	if( Engine::Instance->GetKeyState(irr::KEY_KEY_S) || Engine::Instance->GetKeyState(irr::KEY_RSHIFT) || Engine::Instance->GetKeyState(irr::KEY_HOME) )
	{
		CurrentThrust -= 0.2f;
		if( CurrentThrust < MinimumThrust )
		{
			CurrentThrust = MinimumThrust;
		}
	}

	if( leftWeapon != 0 )
	{
		if( Engine::Instance->GetKeyState(irr::KEY_KEY_A) || Engine::Instance->GetKeyState(irr::KEY_NEXT) )
		{
			leftWeapon->Fire();
		}
		leftWeapon->Update();
	}
	if( rightWeapon != 0 )
	{
		if( Engine::Instance->GetKeyState(irr::KEY_KEY_D) || Engine::Instance->GetKeyState(irr::KEY_END) )
		{
			leftWeapon->Fire();
		}
		rightWeapon->Update();
	}
}
