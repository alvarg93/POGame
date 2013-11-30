#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "functions.h"
struct ControlResponse {
	bool respond;
	char* identifier;
	int code;
};

class Control {
protected:
	SDL_Rect pos;
	char* identifier;
	Uint8 color[4];
public:
	Control();
	Control( char* identifier, int x, int y, int w, int h){
		this->pos.x=x; this->pos.y=y; this->pos.h=h; this->pos.w=w; this->identifier=identifier;
		this->color[0] = 145; this->color[1] = 145; this->color[2] = 145; this->color[3] = 200;
	}
	virtual void display(SDL_Renderer *renderer, TTF_Font *font)=0;
	virtual ControlResponse click(int msX, int msY, bool buttons[5])=0;
	void setColor(unsigned int color[4]);
	void setColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
};

class Button:public Control {
protected:
	bool state;
public:
	Button(char* identifier, int x, int y, int w, int h);
	ControlResponse click(int msX, int msY, bool buttons[5]);
	void display(SDL_Renderer *renderer, TTF_Font *font);
};

class CheckBox:public Control {
private:
public:
	
	bool state;
	CheckBox(char* identifier, int x, int y, int w, int h);
	ControlResponse click(int msX, int msY, bool buttons[5]);
	void display(SDL_Renderer *renderer, TTF_Font *font);
};

class RadioBoxMenu:public Control{
protected:
	int state;
	SDL_Rect pos2[50];
	int amount, marginx, marginy, spacingx, spacingy;
public:
	RadioBoxMenu(char* identifier, int x, int y, int w, int h, int amount);
	ControlResponse click(int msX, int msY, bool buttons[5]);
	void display(SDL_Renderer *renderer, TTF_Font *font);
	void changeOffset(int plusmrgx, int plusmrgy, int plusspcx, int plusspcy);
};

void drawCircle(SDL_Renderer* renderer, int x, int y, int r);
