#include "Control.h"

#include "Singleton.h"
#include "GameStatus.h"
#include "Camera.h"
#include "Graphics.h"

void Control::KeyboardDownFunc(unsigned char key, int x, int y){
	GameStatus* game_status_instance = Singleton<GameStatus>::Instance();
	Camera* camera_instance = Singleton<Camera>::Instance();
	Graphics** graphics_handler_instance = Singleton<Graphics*>::Instance();

	switch (*game_status_instance){
	case GAME_PLAYING: {
		switch (key){
		case 'w':
		case 'W':
			camera_instance->MoveForward();
			key_pressed = 'w';
			break;

		case 's':
		case 'S':
			camera_instance->MoveBackward();
			key_pressed = 's';
			break;

		case 'a':
		case 'A':
			camera_instance->MoveLeft();
			key_pressed = 'a';
			break;

		case 'd':
		case 'D':
			camera_instance->MoveRight();
			key_pressed = 'd';
			break;

		case 'k':
		case 'K':
			(*graphics_handler_instance)->OpenPolygonMode();
			key_pressed = 'k';
			break;

		case 'm':
		case 'M':
			(*game_status_instance) = GAME_HELP_MENU;
			key_pressed = 'm';
			break;

		case 27:
			(*game_status_instance) = GAME_MAIN_MENU;
			break;

		case 'x':
		case 'X':
			(*game_status_instance) = GAME_CREDIT_PAGE;
			key_pressed = 'x';
			break;

		case 'f':
		case 'F':
			key_pressed = 'f';
			break;

		default:
			break;
		}
	}
	break;

	case GAME_MAIN_MENU:{
		switch (key){
		case 27:
			(*game_status_instance) = GAME_PLAYING;
			break;

		default:
			break;
		}
	}
	break;

	case GAME_HELP_MENU: {
		switch (key){
		case 27:
		case 'm':
		case 'M':
			(*game_status_instance) = GAME_PLAYING;
			key_pressed = 'm';
			break;

		default:
			break;
		}
	}
	break;

	case GAME_CREDIT_PAGE: {
		switch (key){
		case 27:
			(*game_status_instance) = GAME_PLAYING;
			break;

		case 'x':
		case 'X':
			(*game_status_instance) = GAME_DONE;
			key_pressed = 'x';
			break;

		default:
			break;
		}
	}
	break;
	}
}

void Control::KeyboardUpFunc(unsigned char key, int x, int y){
	Graphics** graphics_handler_instance = Singleton<Graphics*>::Instance();
	Camera* camera_instance = Singleton<Camera>::Instance();
	switch (key){
	case 'w':
	case 'W':
	case 's':
	case 'S':
		camera_instance->SetIsMovingFB(false);
		key_pressed = 0;
		break;
	case 'a':
	case 'A':
	case 'd':
	case 'D':
		camera_instance->SetIsMovingLR(false);
		key_pressed = 0;
		break;

	case 'f':
	case 'F':
		key_pressed = 0;
		break;

	case 'k':
	case 'K':
		(*graphics_handler_instance)->ClosePolygonMode();
		key_pressed = 0;
		break;

	default:
		break;
	}

}

void Control::MouseMovementFunc(int x, int y){
	Graphics** graphics_handler_instance = Singleton<Graphics*>::Instance();
	Camera* camera_instance = Singleton<Camera>::Instance();
	if (x != mouse_x_org || y != mouse_y_org){
		camera_instance->SetCameraRotation(
			((double)x - ((double)((*graphics_handler_instance)->GetScreenWidth())/2)),
			((double)y - ((double)((*graphics_handler_instance)->GetScreenHeight()) / 2))
			);
		camera_instance->SetIsRotating(true);
		(*graphics_handler_instance)->WarpPointerToCentre();
	}
	else{
		camera_instance->SetIsRotating(false);
	}

	mouse_x_org = x;
	mouse_y_org = y;
}