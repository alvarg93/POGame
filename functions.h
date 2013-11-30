#ifndef _FUNCTIONS
#define _FUNCTIONS


#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static int screen_width=1366, screen_height=768;
static const int FPS = 60;
static bool quit;
static SDL_Renderer *sdlRenderer;
static SDL_Window *sdlWindow;
static int msx =0,msy = 0;
static const Uint8* keys;
static int SDL_BUTTON_WHEELUP = 4;
static int SDL_BUTTON_WHEELDOWN = 5;
static int gamestate = 1;
static bool buttons[5];
static TTF_Font *font;



int Init();
int deInit();
void Quit();
void WaitFrame(int fps);
void KeyHandler();
void ProcessEvents();
void DoEngine();
void Render(int gamestate);
void HandleMouseBtnDown(Uint8 button);
void HandleMouseBtnUp(Uint8 button);
void StartEngine();

template <class T>
T Min (T a,T b) {
 return (a<b?a:b);
}

template <class T>
T Max (T a, T b) {
 return (a>b?a:b);
}


#endif
