#include "gui.h"

Button::Button(char *identifier, int x, int y, int w, int h) : Control(identifier, x, y, w, h){};

CheckBox::CheckBox(char *identifier, int x, int y, int w, int h) : Control(identifier, x, y, w, h){
	this->state=false;
};

RadioBoxMenu::RadioBoxMenu( char *identifier, int x, int y, int w, int h, int amount):Control(identifier,x,y,w,h){
	if(amount>50) this->amount=50; else if(amount<1) this->amount = 1; else this->amount=amount;
	this->state=0;
	this->marginy = 13;
	this->marginx = 10;
	this->spacingy = 23;
	this->spacingx = 3;
	int j=0;
	for(int i=0;i<amount;i++)
		{
			if(2*marginy+j*spacingy>this->pos.h){j=0;spacingx+=60;};
			pos2[i].x=this->pos.x+marginx+spacingx;
			pos2[i].y=this->pos.y+marginy+j*spacingy;
			pos2[i].w=pos2[i].h=8;
			
			j++;
	};
};
void Control::setColor(unsigned int color[4])
{
	for(int i=0;i<4;i++)
		this->color[i] = ((color[i]<=255) ? color[i] : 255);
};

void Control::setColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	this->color[0] = ((r<=255) ? r : 255);
	this->color[1] = ((g<=255) ? g : 255);
	this->color[2] = ((b<=255) ? b : 255);
	this->color[3] = ((a<=255) ? a : 255);
};

ControlResponse Button::click(int msX, int msY, bool buttons[5])
{
	ControlResponse response;
	if((buttons[0])&&(msX>=this->pos.x-this->pos.w)&&(msX<=this->pos.x+this->pos.w)&&(msY>=this->pos.y-this->pos.h)&&(msY<=this->pos.y+this->pos.h))
	{
		state=true;
		buttons[0]=false;
		response.identifier=this->identifier;
		response.respond=true;
		response.code=0;
	}
	else
	{
		response.identifier=this->identifier;
		response.respond=false;
		response.code=0;
	}
	return response;
};

ControlResponse CheckBox::click(int msX, int msY, bool buttons[5])
{
	ControlResponse response;
	if((buttons[0]==true)&&(msX>=this->pos.x)&&(msX<=this->pos.x+this->pos.w)&&(msY>=this->pos.y)&&(msY<=this->pos.y+this->pos.h))
	{
		buttons[0]=false;
		this->state=!(this->state);
		response.identifier=this->identifier;
		response.respond=true;
		response.code=0;
	}
	else
	{
		response.identifier=this->identifier;
		response.respond=false;
		response.code=0;
	}
	return response;
};

void Button::display(SDL_Renderer *renderer, TTF_Font *font)
{
	if(!state){
		SDL_SetRenderDrawColor( renderer, 
		(((this->color[0]+50)>255) ? 255 : this->color[0]+50), 
		(((this->color[0]+50)>255) ? 255 : this->color[0]+50), 
		(((this->color[0]+50)>255) ? 255 : this->color[0]+50), 
		this->color[3] );		
		SDL_RenderFillRect( renderer, &this->pos );

		SDL_Rect outlineRect = { this->pos.x+2, this->pos.y+2, this->pos.w-4, this->pos.h-4 };	
		SDL_SetRenderDrawColor( renderer, color[0], color[1], color[2], color[3] );		
		SDL_RenderFillRect( renderer, &outlineRect );
	}
	else
	{
		SDL_SetRenderDrawColor( renderer, 
		(((this->color[0]+50)>255) ? 255 : this->color[0]+50), 
		(((this->color[1]+50)>255) ? 255 : this->color[1]+50), 
		(((this->color[2]+50)>255) ? 255 : this->color[2]+50), 
		this->color[3] );	
		SDL_RenderFillRect( renderer, &this->pos );

		SDL_Rect outlineRect = { this->pos.x+2, this->pos.y+2, this->pos.w-4, this->pos.h-4 };	
		SDL_SetRenderDrawColor( renderer, color[0]+30, color[1]+30, color[2]-30, color[3] );		
		SDL_RenderFillRect( renderer, &outlineRect );
		

	}

	double x=this->pos.x+(this->pos.w*0.2);
	double y=this->pos.y+(this->pos.h*0.2);
	double w=0.6*this->pos.w;
	double h=0.6*this->pos.h;
	SDL_Rect textbox = { (int)x, (int)y, (int)w, (int)h };	
	SDL_Color color2 = {50, 50, 50};
	SDL_Surface *message = TTF_RenderText_Solid(font, this->identifier, color2);
	SDL_Texture * fontTexture = SDL_CreateTextureFromSurface(renderer, message);
	SDL_FreeSurface(message);
	SDL_RenderCopy(renderer,fontTexture,NULL,&textbox);
	SDL_DestroyTexture(fontTexture);
	state=false;
};

void CheckBox::display(SDL_Renderer *renderer, TTF_Font *font)
{
	
	SDL_SetRenderDrawColor( renderer, 
		(((this->color[0]+50)>255) ? 255 : this->color[0]+50), 
		(((this->color[1]+50)>255) ? 255 : this->color[1]+50), 
		(((this->color[2]+50)>255) ? 255 : this->color[2]+50), 
		this->color[3] );		
	SDL_RenderFillRect( renderer, &this->pos );

	SDL_Rect outlineRect = { this->pos.x+2, this->pos.y+2, this->pos.w-4, this->pos.h-4 };	
	SDL_SetRenderDrawColor( renderer, color[0], color[1], color[2], color[3] );		
	SDL_RenderFillRect( renderer, &outlineRect );


	if(state)
	{
		SDL_Rect selectionRect = { this->pos.x+3, this->pos.y+3, this->pos.w-6, this->pos.h-6 };
		SDL_SetRenderDrawColor( renderer, 
			(((this->color[0]-30)<0) ? 0 : this->color[0]-30), 
			(((this->color[1])>255) ? 255 : this->color[1]), 
			(((this->color[2]-30)<0) ? 0 : this->color[2]-30), 
			this->color[3] );		
		SDL_RenderFillRect( renderer, &selectionRect );

		SDL_Rect selectionRect2 = { this->pos.x+5, this->pos.y+5, this->pos.w-10, this->pos.h-10 };
		SDL_SetRenderDrawColor( renderer, 0, 255, 0, this->color[3]);		
		SDL_RenderFillRect( renderer, &selectionRect2 );
	}

	
};

void drawCircle(SDL_Renderer* renderer, int x, int y, int r)
{
	SDL_Point* pixels;
	int amount=0;
	for(int i=-r;i<=r;i++)
		for(int j=-r;j<=r;j++)
			if(j*j+i*i<=r*r)amount++;
	pixels=new SDL_Point[amount];
	amount=0;
	for(int i=-r;i<=r;i++)
		for(int j=-r;j<=r;j++)
			if(j*j+i*i<r*r){pixels[amount].x=j+x; pixels[amount].y=i+y; amount++;};
	SDL_RenderDrawPoints(renderer,pixels,amount);
	delete [] pixels;
};

void RadioBoxMenu::display(SDL_Renderer *renderer, TTF_Font *font)
{
		SDL_SetRenderDrawColor( renderer, 
		(((this->color[0]+50)>255) ? 255 : this->color[0]+50), 
		(((this->color[1]+50)>255) ? 255 : this->color[1]+50), 
		(((this->color[2]+50)>255) ? 255 : this->color[2]+50), 
		255 );		
		SDL_RenderFillRect( renderer, &this->pos );

		SDL_Rect outlineRect = { this->pos.x+3, this->pos.y+3, this->pos.w-6, this->pos.h-6 };	
		SDL_SetRenderDrawColor( renderer, this->color[0], this->color[1], this->color[2], this->color[3] );		
		SDL_RenderFillRect( renderer, &outlineRect );

		for(int i=0;i<this->amount;i++)
		{
			SDL_SetRenderDrawColor( renderer, this->color[0]-50, this->color[1]-50, this->color[2]-50, this->color[3]);
			drawCircle(renderer,this->pos2[i].x,this->pos2[i].y,this->pos2[i].h);
			SDL_SetRenderDrawColor( renderer, this->color[0]+70, this->color[1]+70, this->color[2]+70, this->color[3] );	
			drawCircle(renderer,this->pos2[i].x,this->pos2[i].y,this->pos2[i].h-1);	
		}
		
		if(this->state)
		{
			SDL_SetRenderDrawColor( renderer, (((this->color[0]-30)<0) ? 0 : this->color[0]-30), (((this->color[1])>255) ? 255 : this->color[1]), (((this->color[2]-30)<0) ? 0 : this->color[2]-30), this->color[3] );
			drawCircle(renderer,this->pos2[state-1].x,this->pos2[state-1].y,this->pos2[state-1].h-2);
			SDL_SetRenderDrawColor( renderer, 0, 255, 0, this->color[3]);		
			drawCircle(renderer,this->pos2[state-1].x,this->pos2[state-1].y,this->pos2[state-1].h-4);
		}

};

ControlResponse RadioBoxMenu::click(int msX, int msY, bool buttons[5])
{
	ControlResponse response;
    response.respond=true;
	response.identifier=this->identifier;
	response.code=this->state;
	int i=0;
	for(i;i<amount;i++)
		if(!(msY>this->pos2[i].y+this->pos2[i].h)&&!(msX>this->pos2[i].x+this->pos2[i].w)) if((buttons[0]==true)&&(msX>=this->pos2[i].x-this->pos2[i].w)&&(msX<=this->pos2[i].x+this->pos2[i].w)&&(msY>=this->pos2[i].y-this->pos2[i].h)&&(msY<=this->pos2[i].y+this->pos2[i].h)) {response.code=i+1;break;};
	this->state=response.code;
	return response;
};

void RadioBoxMenu::changeOffset(int plusmrgx, int plusmrgy, int plusspcx, int plusspcy){
	this->marginx=Max(0,this->marginx+plusmrgx);
	this->marginx=Max(0,this->marginy+plusmrgy);
	this->marginx=Max(0,this->spacingx+plusspcx);
	this->marginx=Max(0,this->spacingy+plusspcy);
}
