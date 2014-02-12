
#include "craft.h"
#include "engine.h"

Craft::Craft( core::vector3df Position, core::vector3df Rotation ) : Body(Position, Rotation)
{
	Cam = 0;
	CurrentThrust = 2;
	MaximumThrust = 20.0;
	MinimumThrust = 0.0;
	TurnSpeed = 1.5;
	Acceleration = 0.4;
	Deceleration = 0.3;
}


void Craft::SetCamera(scene::ICameraSceneNode *Camera)
{
	Cam = Camera;
}


void Craft::setModel()
{
	Model = Engine::Instance->GetSceneManager()->addAnimatedMeshSceneNode( Engine::Instance->GetSceneManager()->getMesh("resource/X-17 Viper flying.obj") );  // addCubeSceneNode();
	Model->setMaterialFlag( video::EMF_LIGHTING, false );
	Model->setScale( core::vector3df(0.1f) );
}

void Craft::makeCockpit(irr::core::vector3df offset)
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

void Craft::Update()
{
	Body::Update();
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
		CurrentThrust += Acceleration;
		if( CurrentThrust > MaximumThrust )
		{
			CurrentThrust = MaximumThrust;
		}
	}
	if( Engine::Instance->GetKeyState(irr::KEY_KEY_S) || Engine::Instance->GetKeyState(irr::KEY_RSHIFT) || Engine::Instance->GetKeyState(irr::KEY_HOME) )
	{
		CurrentThrust -= Deceleration;
		if( CurrentThrust < MinimumThrust )
		{
			CurrentThrust = MinimumThrust;
		}
	}
}
