#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static const int FPS = 60;
static bool quit;
static SDL_Renderer *sdlRenderer;
static SDL_Window *sdlWindow;
static int *msx,*msy;
static const Uint8* keys;
static int SDL_BUTTON_WHEELUP = 4;
static int SDL_BUTTON_WHEELDOWN = 5;
static int gamestate = 1;

int Init();
int deInit();
void Quit();
void WaitFrame(int fps);
void KeyHandler();
void ProcessEvents();
void DoEngine();
void Render();
void HandleMouseBtn();
void StartEngine();
