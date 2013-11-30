#include "functions.h"
#include "classes.h"


Button przycisk = Button("przycisk",100,100,200,50);
CheckBox przycisk2 = CheckBox("przycisk 2",320,100,20,20);
RadioBoxMenu menu = RadioBoxMenu("menu1",800,500,200,35,3);

int SDL_main(int argc, char *argv[])
{
	Init();
	quit=false;
	while (!quit) {
			WaitFrame(FPS);
			KeyHandler();
			ProcessEvents();
			DoEngine();
			Render(gamestate);

			//Clear screen

				//Render red filled quad
				

				buttons[0]=false;
	}




	
	deInit();
	return 0;
}


void ProcessEvents()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_MOUSEMOTION:
			msx=event.motion.x;
			msy=event.motion.y;
			break;

		case SDL_MOUSEBUTTONDOWN:
			HandleMouseBtnDown(event.button.button);
			break;

		case SDL_MOUSEBUTTONUP:
			HandleMouseBtnUp(event.button.button);
			break;

		case SDL_QUIT:
			quit=true;
			break;

		}
	}
}

void KeyHandler(){
	//klawiatura
	keys = SDL_GetKeyboardState(NULL);
	//switch(gamestate)
	if(keys[SDLK_RIGHT])
	{
		
	}

	if(keys[SDLK_LEFT])
	{
		
	}

	if(keys[SDLK_UP])
	{
		
	}

	if(keys[SDLK_DOWN])
	{
		
	}
	if(keys[SDLK_a])
	{
		
	}
	if(keys[SDL_SCANCODE_ESCAPE])
	{
		quit=true;
	}
}

int Init()
{
	//inicjalizacja SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
	//std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	return 1;
	}

	//inicjalizacja okna
	SDL_Window *window = SDL_CreateWindow(	"Game",
											SDL_WINDOWPOS_UNDEFINED,
											SDL_WINDOWPOS_UNDEFINED,
											screen_width, screen_height,
											SDL_WINDOW_FULLSCREEN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	sdlWindow=window;
	sdlRenderer=renderer;
	//inicjalizacja SDL_image
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
	//std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
	return 2;
	}

	//inicjalizacja SDL_ttf
	if (TTF_Init() != 0)
	//std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
	return 3;

	//inicjalizacja SDL_mixer
	if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
	{
	//std::cout << "Mix_Init Error: " << Mix_GetError() << std::endl;
	return 4;
	}

	font = TTF_OpenFont("arial.ttf", 30);

	for(int i=0;i<5;i++)
		buttons[i]=false;


	return 0;
}

int deInit()
{
	TTF_CloseFont(font);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
	return 0;
}

void Quit(){
	quit=true;
}

void WaitFrame(int fps)
{
	static int next_tick=0;
	int this_tick;

	this_tick = SDL_GetTicks();
	if(this_tick < next_tick)
		SDL_Delay(next_tick-this_tick);
	next_tick = SDL_GetTicks() + (1000/fps);
}


void HandleMouseBtnDown(Uint8 button)
{
	//switch(gamestate)
	if(button==SDL_BUTTON_LEFT){
		buttons[0]=true;
		
	}

	if(button==SDL_BUTTON_RIGHT) 
		buttons[2]=true;

}

void HandleMouseBtnUp(Uint8 button)
{
	//switch(gamestate)
	if(button==SDL_BUTTON_LEFT){
		buttons[0]=false;
	}

	if(button==SDL_BUTTON_RIGHT) 
		buttons[2]=false;


}

void StartEngine()
{

}

void DoEngine()
{

}
void Render(int gamestate)
{
	switch(gamestate)
	{
	case 1:
		{
			SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
			SDL_RenderClear(sdlRenderer);
			SDL_Rect background = {0,100,screen_width,screen_height-200};
			SDL_Surface *menuback = IMG_Load("Images/menu.jpg");
			SDL_Texture * texture = SDL_CreateTextureFromSurface(sdlRenderer, menuback);
			SDL_FreeSurface(menuback);
			SDL_RenderCopy(sdlRenderer,texture,&background,&background);
			
			przycisk.display(sdlRenderer, font);
			przycisk.click(msx,msy, buttons);
			przycisk2.display(sdlRenderer, font);
			przycisk2.click(msx,msy, buttons);
			menu.display(sdlRenderer, font);
			menu.click(msx,msy,buttons);

			SDL_RenderPresent( sdlRenderer );
			SDL_DestroyTexture(texture);
		};
		break;


				
				
				
		


	default:
		SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
		SDL_RenderClear(sdlRenderer);
		SDL_RenderPresent( sdlRenderer );
	};
}
