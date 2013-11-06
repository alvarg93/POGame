#include "functions.h"
#include "classes.h"

int SDL_main(int argc, char *argv[])
{
	Init();
	
	quit=false;
	while (!quit) {
			WaitFrame(FPS);
			KeyHandler();
			ProcessEvents();
			DoEngine();
			Render();
	}




	
	//deInit();
	exit(0);
	return 0;
}
