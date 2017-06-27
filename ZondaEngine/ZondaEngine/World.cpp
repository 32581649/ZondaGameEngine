#include <iostream>

#include "World.h"

#include "Singleton.h"
#include "Camera.h"
#include "GameTime.h"

World::~World(){
	if ((*graphics_handler)){
		delete *graphics_handler;
		*graphics_handler = NULL;
	}
}

void World::RunGame(int* argc, char* argv[], const char* window_name, const char* api, const int & screen_width, const int & screen_height){
	*graphics_handler = graphics_factory.Create(api);
	if (!(*graphics_handler)){
		std::cout << "graphics_handler = NULL" << std::endl;
		getchar();
		return;
	}

	if (api == "OpenGL"){
		(*graphics_handler)->CreateGameWindow(screen_width, screen_height,
			window_name,
			argc, argv);
	}
}

void World::UpdateGame(){
	GameTime* game_time_instance = Singleton<GameTime>::Instance();
	elapsed_time_second = game_time_instance->GetElapsedTimeSecond();
	fps = game_time_instance->GetFps();

	Camera* camera_instance = Singleton<Camera>::Instance();
	camera_instance->SetCameraSpdWithDT(elapsed_time_second);
	camera_instance->CheckCamera();

	GameStatus* game_status_instance = Singleton<GameStatus>::Instance();
	if ((*game_status_instance) != GAME_PLAYING){
		if ((*game_status_instance) == GAME_DONE){
			GameDestruction();
			exit(0);
		}

		if ((*game_status_instance) == GAME_MAIN_MENU){
			// ui.mainMenu(512, 512, 0, 0); //texture2d.Display2DTexture(512, 512, 0, 0, GAME_MAIN_MENU_TEXTURE);
		}

		if ((*game_status_instance) == GAME_HELP_MENU){
			//texture2d.Display2DTexture(512, 512, 0, 0, GAME_HELP_MENU_TEXTURE);
		}

		if ((*game_status_instance) == GAME_CREDIT_PAGE){
			//texture2d.Display2DTexture(512, 512, 0, 0, CREDIT_TEXTURE);
		}

	}
}