
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

	timeDeltaTime = 0;
	timeFrameTime = 1000 / 50;	// 50FPS default

	//ply = new Player();
	//ply->SetCamera( camera );

	Craft* ply = new Craft( core::vector3df(0), core::vector3df(0) );
	ply->SetCamera( camera );
	Objects.push_back( ply );


	for( int zX = -16; zX <= 16; zX += 4 )
	{
		for( int zY = -16; zY <= 16; zY += 4 )
		{
			for( int zZ = -16; zZ <= 16; zZ += 4 )
			{
				scene::ISceneNode* node2 = sceneManager->addCubeSceneNode(); //just for reference
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
}

bool Engine::GetKeyState( int KeyID )
{
	return keys[KeyID];
}

/*
int main()
{
	float playerThrust = 0.6f;
	float playerTurn = 2.4f - playerThrust;

	

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	scene::ISceneNode* node1 = smgr->addCubeSceneNode(); //replace with what ever you want
	if (node1)
		node1->setMaterialFlag(video::EMF_LIGHTING, false);

	for( int zX = -4; zX <= 4; zX += 4 )
	{
		for( int zY = -4; zY <= 4; zY += 4 )
		{
			for( int zZ = -4; zZ <= 4; zZ += 4 )
			{
				scene::ISceneNode* node2 = smgr->addCubeSceneNode(); //just for reference
				if (node2)
				{
					node2->setMaterialFlag(video::EMF_LIGHTING, false);
					node2->setPosition(core::vector3df( 100 * zX, 100 * zY, 100 * zZ));
				}

			}
		}
	}


	scene::ICameraSceneNode *camera = device->getSceneManager()->addCameraSceneNode();

	while(device->run())
	{

		// direction control
		if(keys[irr::KEY_LEFT])
		{
			turn(node1, -playerTurn);
		}
		if(keys[irr::KEY_RIGHT])
		{
			turn(node1, playerTurn);
		}
		if(keys[irr::KEY_UP])
		{
			pitch(node1, playerTurn);
		}
		if(keys[irr::KEY_DOWN])
		{
			pitch(node1, -playerTurn);
		}
		if(keys[irr::KEY_COMMA] || keys[irr::KEY_HOME])
		{
			roll(node1, playerTurn);
		}
		if(keys[irr::KEY_PERIOD] || keys[irr::KEY_END])
		{
			roll(node1, -playerTurn);
		}

		if(keys[irr::KEY_RSHIFT] || keys[irr::KEY_NEXT])
		{
			playerThrust -= 0.2f;
			if( playerThrust < 0.1f )
			{
				playerThrust = 0.1f;
			}
			playerTurn = 2.4f - playerThrust;
		}

		if(keys[irr::KEY_RCONTROL] || keys[irr::KEY_PRIOR])
		{
			playerThrust += 0.2f;
			if( playerThrust > 2.0f )
			{
				playerThrust = 2.0f;
			}
			playerTurn = 2.4f - playerThrust;
		}

		// movement control
		if(keys[irr::KEY_KEY_W])
		{
		move(node1, core::vector3df(0,0,0.1));
		}
		if(keys[irr::KEY_KEY_S])
		{
		move(node1, core::vector3df(0,0,-0.1));
		}

		move(node1, core::vector3df(0,0,playerThrust));

		makeCockpit(camera, node1, core::vector3df(0,7,-30));

		driver->endScene();

		if( keys[irr::KEY_ESCAPE] || keys[irr::KEY_KEY_Q])
		{
			device->closeDevice();
		}
	}

	device->drop();

	return 1;
}
*/