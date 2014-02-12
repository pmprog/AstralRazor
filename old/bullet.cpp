
#include "bullet.h"
#include "engine.h"

Bullet::Bullet()
{
	CurrentThrust = 20.0f;
	MinimumThrust = 8.0f;
	MaximumThrust = 30.0f;
	TurnSpeed = 1.5f;

	//scene::IAnimatedMesh fighterMesh = ;
	Model = Engine::Instance->GetSceneManager()->addCubeSceneNode();
	Model->setMaterialFlag( video::EMF_LIGHTING, false );
}

void Bullet::move(irr::core::vector3df vel)
{
	irr::core::matrix4 m;
	m.setRotationDegrees(Model->getRotation());
	m.transformVect(vel);
	Model->setPosition(Model->getPosition() + vel);
	Model->updateAbsolutePosition();
}

void Bullet::rotate(irr::core::vector3df rot)
{
	irr::core::matrix4 m;
	m.setRotationDegrees(Model->getRotation());
	irr::core::matrix4 n;
	n.setRotationDegrees(rot);
	m *= n;
	Model->setRotation( m.getRotationDegrees() );
	Model->updateAbsolutePosition();
}

void Bullet::turn(irr::f32 rot)
{
	rotate(irr::core::vector3df(0.0f, rot, 0.0f) );
}

void Bullet::pitch(irr::f32 rot)
{
	rotate(irr::core::vector3df(rot, 0.0f, 0.0f) );
}

void Bullet::roll(irr::f32 rot)
{
	rotate(irr::core::vector3df(0.0f, 0.0f, rot) );
}

void Bullet::Update()
{
	move( core::vector3df( 0, 0, CurrentThrust ) );
}
