#include "engine.h"
#include "body.h"
#include "craft.h"

Engine* Engine::Instance;

Engine::Engine()
{
	Instance = this;

	for( s32 i = 0; i < KEY_KEY_CODES_COUNT; i++ )
	{
		keys[i] = false;
	}

	IrrlichtDevice* nullDev = createDevice( video::EDT_NULL );
	core::dimension2d<u32> deskRes = nullDev->getVideoModeList()->getDesktopResolution();
	s32 deskBPP = nullDev->getVideoModeList()->getDesktopDepth();
	nullDev->drop();

#ifdef _DEBUG
	deskRes.Width -= 64;
	deskRes.Height -= 128;
	device = createDevice(driverChoiceConsole(false), deskRes, deskBPP, false, false, false, this);
#else
	device = createDevice(driverChoiceConsole(false), deskRes, deskBPP, true, false, false, this);
#endif
	driver = device->getVideoDriver();
	sceneManager = device->getSceneManager();

	camera = sceneManager->addCameraSceneNode();
	sceneParent = sceneManager->addEmptySceneNode();

	timeDeltaTime = 0;
	timeFrameTime = 1000 / 50;	// 50FPS default

	//ply = new Player();
	//ply->SetCamera( camera );

	Craft* ply = new Craft( core::vector3df(0), core::vector3df(0) );
	ply->SetCamera( camera );
	Objects.push_back( ply );


	for( int zX = -64; zX <= 64; zX += 8 )
	{
		for( int zY = -64; zY <= 64; zY += 8 )
		{
			for( int zZ = -64; zZ <= 64; zZ += 8 )
			{
				scene::ISceneNode* node2 = sceneManager->addCubeSceneNode();
				if (node2)
				{
					node2->setMaterialFlag(video::EMF_LIGHTING, false);
					node2->setPosition(core::vector3df( 100 * zX, 100 * zY, 100 * zZ));
				}

			}
		}
	}

}

Engine::~Engine()
{
	device->drop();
}

IrrlichtDevice* Engine::GetDevice()
{
	return device;
}

scene::ISceneManager* Engine::GetSceneManager()
{
	return sceneManager;
}

bool Engine::OnEvent(const SEvent &event)
{
	if(event.EventType == EET_KEY_INPUT_EVENT)
	{
		keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
		return true;
	}
	return false;
}


void Engine::Run()
{

	timeLastCheck = device->getTimer()->getTime();
	while( device->run() )
	{
		driver->beginScene( true, true, video::SColor(0, 24,32,64) );
		Render();
		driver->endScene();

		u32 timeCurrent = device->getTimer()->getTime();
		timeDeltaTime += (timeCurrent - timeLastCheck);
		timeLastCheck = device->getTimer()->getTime();
		while( timeDeltaTime > timeFrameTime )
		{
			Update();
			timeDeltaTime -= timeFrameTime;
		}

		if( keys[irr::KEY_ESCAPE] || keys[irr::KEY_KEY_Q])
		{
			device->closeDevice();
		}

	}

}

void Engine::Render()
{
	sceneManager->drawAll();
}

void Engine::Update()
{
	for( std::vector<Body*>::iterator i = Objects.begin(); i != Objects.end(); i++ )
	{
		Body* b = (*i);
		b->Update();
	}

	while( ObjectsToAdd.size() > 0 )
	{
		Objects.push_back( ObjectsToAdd.back() );
		ObjectsToAdd.pop_back();
	}
}

bool Engine::GetKeyState( int KeyID )
{
	return keys[KeyID];
}

scene::IAnimatedMesh* Engine::LoadMeshFile( std::string Filename )
{
	return sceneManager->getMesh( Filename.c_str() );
}

void Engine::AddBody( Body* NewBody )
{
	ObjectsToAdd.push_back( NewBody );
}

scene::ISceneNode* Engine::GetSceneParentNode()
{
	return sceneParent;
}
