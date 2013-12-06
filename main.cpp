#include "functions.h"
#include "classes.h"


//Button przycisk = Button("przycisk",100,100,200,50);
//CheckBox przycisk2 = CheckBox("przycisk 2",320,100,20,20);
//RadioBoxMenu menu = RadioBoxMenu("menu1",800,500,200,35,3);
VisibleObject *objects[NUM_OF_OBJ];
int numofobj=0;
std::fstream levels[10];


int SDL_main(int argc, char *argv[])
{
	Init();
	StartEngine();
	quit=false;
	while (!quit) {
			WaitFrame(FPS);
			KeyHandler();
			ProcessEvents();
			DoEngine();
			Render();

			//Clear screen

				//Render red filled quad
				
			
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
			msxrel=event.motion.xrel;
			msyrel=event.motion.yrel;
			if((gamestate==1)&&((msxrel)||(msyrel)))
			{
				if(msy<533)mainmenu=0;
				else if((msy>=533)&&(msy<568))mainmenu=1;
				else if((msy>=560)&&(msy<603))mainmenu=2;
				else if(msy>=603) mainmenu=3;
			};
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
	int a=5;
	keys = SDL_GetKeyboardState(NULL);
	if(keys[SDL_SCANCODE_RIGHT])
	{
		if(gamestate==2){
			map_offset.x+=10;
		}
	}
			
	if(keys[SDL_SCANCODE_LEFT])
	{
		if(gamestate==2){
			map_offset.x=Max(0,map_offset.x-10);
		}
	}

	if(keys[SDL_SCANCODE_UP])
	{
		if(gamestate==1){
		mainmenu--;
		mainmenu=Max(0,mainmenu);
		}

		if(gamestate==2){
			map_offset.y-=10;

		}
	}

	if(keys[SDL_SCANCODE_DOWN])
	{
		if(gamestate==1){
		mainmenu++;
		mainmenu=Min(3,mainmenu);
		}

		if(gamestate==2){
			map_offset.y+=10;
		}
	}

	if(keys[SDL_SCANCODE_RETURN])
	{
		if(gamestate==1)
			switch(mainmenu)
		{
			case 0:
				gamestate=2;
				break;
			case 3:
				quit=true;
				break;

		}


	}

	if(keys[SDL_SCANCODE_ESCAPE])
	{
		if(gamestate==2)gamestate=1;
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

	return 0;
}

int deInit()
{
	Mix_FreeMusic(music[0]);
	Mix_CloseAudio();

	for(int i=0;i<num_of_text;i++)
		SDL_DestroyTexture(textures[i]);
	
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
		
		if(gamestate==1)
		{
			switch(mainmenu)
			{
			case 0:
				gamestate=2;
				break;
			case 3:
				quit=true;
				break;

			}
		}


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
	font = TTF_OpenFont("arial.ttf", 30);

	for(int i=0;i<5;i++)
		buttons[i]=false;

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_Music *mus = Mix_LoadMUS("sounds/mohicans.mp3");
	music[0]=mus;

	int i=0;
	SDL_Surface *tempimg = IMG_Load("textures/menu.jpg");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/bg1.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/bg2.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/bgmenu.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block1.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block2.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block3.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block4.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block5.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block6.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block7.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block8.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block9.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block10.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block11.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block12.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block13.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block14.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block15.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;
	tempimg = IMG_Load("textures/block16.png");
	textures[i] = SDL_CreateTextureFromSurface(sdlRenderer, tempimg);
	SDL_FreeSurface(tempimg);
	i++;

	num_of_text=i;
	Mix_PlayMusic(music[0], -1);
	
	for(int i=0;i<NUM_OF_OBJ;i++)objects[i]=NULL;

	levels[0].open("level1.txt",std::fstream::in);
	int j=0;
	int back;
	levels[0]>>back;
	int x,y,tex;
	while((!levels[0].eof())&&(j<NUM_OF_OBJ))
	{	
		levels[0]>>x>>y>>tex;
		objects[j]=new StaticObject(x,y,45,45,tex);
		j++;
	}
}

void DoEngine()
{
	int temp=gamestate;
	switch(gamestate)
	{
	case 1:
		if(prevstate!=gamestate)
		{
			Mix_PlayMusic(music[0], -1);	
		};
		break;
	case 2:
		{
			if(prevstate!=gamestate)
				{
			Mix_HaltMusic();		
			};
			
		};
		break;
	case 3:
		if(prevstate!=gamestate);
		break;
	case 4:
		if(prevstate!=gamestate);
		break;
	default: quit=true;

	}
	prevstate=temp;
}
void Render()
{
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
	SDL_RenderClear(sdlRenderer);
	switch(gamestate)
	{
	case 1:
		{
			
			SDL_Rect background = {0,100,screen_width,screen_height-200};
			SDL_RenderCopy(sdlRenderer,textures[0],&background,&background);
			/*
			przycisk.display(sdlRenderer, font);
			przycisk.click(msx,msy, buttons);
			przycisk2.display(sdlRenderer, font);
			przycisk2.click(msx,msy, buttons);
			menu.display(sdlRenderer, font);
			menu.click(msx,msy,buttons);
			*/
			SDL_Rect newgame = { 100, 500, 150, 30};
			SDL_Rect loadgame = { 100, 535, 150, 30};
			SDL_Rect credits = { 100, 570, 100, 30};
			SDL_Rect quitgame = { 100, 605, 150, 30};
			SDL_Color color = {255,255,255};
			SDL_Color color2= {255,255,0};
			SDL_Color colr1,colr2,colr3,colr4;
			colr1=((mainmenu==0) ? color2 : color);
			colr2=((mainmenu==1) ? color2 : color);
			colr3=((mainmenu==2) ? color2 : color);
			colr4=((mainmenu==3) ? color2 : color);
			SDL_Surface *newg = TTF_RenderText_Solid(font, "New Game", colr1);
			SDL_Surface *lodg = TTF_RenderText_Solid(font, "Load Game", colr2);
			SDL_Surface *cred = TTF_RenderText_Solid(font, "Credits", colr3);
			SDL_Surface *quit = TTF_RenderText_Solid(font, "Quit Game", colr4);
			SDL_Texture * newt = SDL_CreateTextureFromSurface(sdlRenderer, newg);
			SDL_Texture * lodt = SDL_CreateTextureFromSurface(sdlRenderer, lodg);
			SDL_Texture * crdt = SDL_CreateTextureFromSurface(sdlRenderer, cred);
			SDL_Texture * qutt = SDL_CreateTextureFromSurface(sdlRenderer, quit);
			SDL_FreeSurface(newg);
			SDL_FreeSurface(lodg);
			SDL_FreeSurface(cred);
			SDL_FreeSurface(quit);
			SDL_RenderCopy(sdlRenderer,newt,NULL,&newgame);
			SDL_RenderCopy(sdlRenderer,lodt,NULL,&loadgame);
			SDL_RenderCopy(sdlRenderer,crdt,NULL,&credits);
			SDL_RenderCopy(sdlRenderer,qutt,NULL,&quitgame);
			SDL_DestroyTexture(newt);
			SDL_DestroyTexture(lodt);
			SDL_DestroyTexture(crdt);
			SDL_DestroyTexture(qutt);
		};
		break;
	case 2:
		{	
			SDL_Rect background = {0,0,screen_width,screen_height};
			SDL_RenderCopy(sdlRenderer,textures[1],&background,&background);
			for(int i=0;i<NUM_OF_OBJ;i++)
				if(objects[i]!=NULL){
					
					SDL_Rect pos=objects[i]->Measures();
					pos.x-=map_offset.x;
					pos.y-=map_offset.y;
					SDL_RenderCopy(sdlRenderer,textures[objects[i]->Texture(-1)],NULL,&pos);
				}

			
		};
		break;

				
				
				
		

	};
	SDL_RenderPresent(sdlRenderer);
}
