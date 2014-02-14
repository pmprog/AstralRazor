
#include "body.h"
#include "engine.h"

Body::Body( scene::IAnimatedMesh* Mesh, core::vector3df Position, core::vector3df Rotation )
{
	CurrentThrust = 0;


	if( Mesh == 0 )
	{
		Model = Engine::Instance->GetSceneManager()->addCubeSceneNode();
		Model->setMaterialFlag( video::EMF_LIGHTING, false );
	} else {
		Model = Engine::Instance->GetSceneManager()->addAnimatedMeshSceneNode( Mesh );
	}
	Model->setPosition( Position );
	Model->setRotation( Rotation );
	
}

Body::~Body()
{
	Model->remove();
}

void Body::move(irr::core::vector3df vel)
{
	irr::core::matrix4 m;
	m.setRotationDegrees(Model->getRotation());
	m.transformVect(vel);
	Model->setPosition(Model->getPosition() + vel);
	Model->updateAbsolutePosition();
}

void Body::rotate(irr::core::vector3df rot)
{
	irr::core::matrix4 m;
	m.setRotationDegrees(Model->getRotation());
	irr::core::matrix4 n;
	n.setRotationDegrees(rot);
	m *= n;
	Model->setRotation( m.getRotationDegrees() );
	Model->updateAbsolutePosition();
}

void Body::turn(irr::f32 rot)
{
	rotate(irr::core::vector3df(0.0f, rot, 0.0f) );
}

void Body::pitch(irr::f32 rot)
{
	rotate(irr::core::vector3df(rot, 0.0f, 0.0f) );
}

void Body::roll(irr::f32 rot)
{
	rotate(irr::core::vector3df(0.0f, 0.0f, rot) );
}

core::vector3df Body::GetPosition()
{
	return Model->getPosition();
}

core::vector3df Body::GetRotation()
{
	return Model->getRotation();
}

void Body::Update()
{
	move( core::vector3df( 0, 0, CurrentThrust ) );
}

f32 Body::GetThrust()
{
	return CurrentThrust;
}

void Body::SetThrust(f32 Thrust)
{
	CurrentThrust = Thrust;
}
