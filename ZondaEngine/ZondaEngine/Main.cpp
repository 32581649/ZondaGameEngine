#include <iostream>
#include "Singleton.h"
#include "World.h"

int main(int argc, char* argv[]){
	//StateTest* a = Singleton<StateTest>::Instance();
	//StateTest* b = Singleton<StateTest>::Instance();

	World* world_instance = Singleton<World>::Instance();
	world_instance->RunGame(&argc, argv, "Zonda Engine Game Demo", "OpenGL", 1024, 768);

	return 0;
}