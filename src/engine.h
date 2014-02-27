#pragma once

#include "graphics.h"
#include <vector>
#include <string>

#ifndef Body
class Body;
#endif

class Engine : public IEventReceiver
{
	private:
		IrrlichtDevice* device;
		bool keys[KEY_KEY_CODES_COUNT];
		video::IVideoDriver* driver;
		scene::ISceneManager* sceneManager;
		scene::ICameraSceneNode* camera;
		scene::ISceneNode* sceneParent;

		u32 timeDeltaTime;
		u32 timeLastCheck;
		u32 timeFrameTime;

		std::vector<Body*> ObjectsToAdd;

	public:
		static Engine* Instance;
		
		std::vector<Body*> Objects;
		

		Engine();
		~Engine();

		IrrlichtDevice* GetDevice();
		scene::ISceneManager* GetSceneManager();

		virtual bool OnEvent(const SEvent &event);

		void Run();
		void Render();
		void Update();

		bool GetKeyState( int KeyID );
		scene::IAnimatedMesh* LoadMeshFile( std::string Filename );

		void AddBody( Body* NewBody );
		scene::ISceneNode* GetSceneParentNode();

};
