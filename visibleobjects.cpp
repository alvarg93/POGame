#include "visibleobjects.h"
#include <SDL.h>
#include <vector>
#include<time.h>
using namespace std;
//	____
//	|	|
//H	|	|
//	|	|
//	  W
//
Player Hero;
vector <StaticObject> SO;
vector <AICharacter> E;
vector <Projectile> P;


int rozmiatpocisku = 2;
int limitbroni1 = 100;
int limitbroni2 = 50;
int limitbroni3 = 20;
int dmgpocisku = 5;
int zasiegpocisku = 100;
//przy zbyt dużej predkości pocisku mogą one przenikać przez ludki - zbadac
int predkoscpocisku = 10;
int predkoscskoku = 10;

void Engine()
{
	int SOs = SO.size(),Es = E.size(),Ps = P.size();
	//przesuniecia//
	Hero.Move();
	for(int i=0;i<Es;i++)E[i].Move();
	for(int i=0;i<Ps;i++)P[i].Move();
	
	//obsługa projectile//
	for(int i=0;i<Ps;i++)if(P[i].BOOM() || P[i].Range() <= 0){/*usuniecie pocisku*/};

	//sprawdzic czy cos umarło//

	
	//obsluga AI//
	for(int i=0;i<Es;i++)E[i].AI();
	
	//obsluga Hero//
	Hero.Action();
}
bool Collide(int x1,int y1,int x2,int y2,int a1,int b1,int a2,int b2)
{
	if(a2>x1 && x2>a1 && b2>y1 && y2>b1)return true;
	return false;
}

VisibleObject::VisibleObject(int x,int y,int w,int h, int texture)  {this->x=x;this->y=y;this->w=w;this->h=h;this->texture=texture;};

StaticObject::StaticObject(int x,int y,int w,int h, int texture) : VisibleObject(x,y,w,h,texture) {};

VisibleObject::VisibleObject(){this->x=0;this->y=0;this->w=0;this->h=0;this->texture=0;};
StaticObject::StaticObject() : VisibleObject(){};

int VisibleObject::Texture(int text)
{
	if(text>=0)	this->texture=text;
	return this->texture;
}

void VisibleObject::SetPos(int x,int y)
{
	this->x = x;
	this->y = y;
}
void VisibleObject::SetPos(int x1,int y1, int x2, int y2)
{
	this->x = x1;
	this->y = y1;
	this->w = x2 - x1;
	this->h = y2 - y1;
}
void VisibleObject::GetPos(int *x,int *y)
{
	*x = this->x;
	*y = this->y;
}
void VisibleObject::GetPos(int *x1,int *y1,int *x2,int *y2)
{
	*x1 = this->x;
	*y1 = this->y;
	*x2 = this->w+*x1;
	*y2 = this->h+*y1;
}

SDL_Rect VisibleObject::Measures()
{
	SDL_Rect r={this->x,this->y,this->w,this->h};
}

void VisibleObject::SetSize(int w,int h)
{
	this->w = w;
	this->h = h;
}
 void VisibleObject::Display(SDL_Renderer *renderer, SDL_Texture **textures)
{
	SDL_Rect pos={this->x,this->y,this->w,this->h};
	SDL_RenderCopy(renderer,textures[texture],&pos,&pos);

}
void StaticObject::SetType(int t){this->type = t;}
void StaticObject::GetType(int *t){*t = this->type;}

void Moveable::SetV(int vx,int vy)
{
	this->vx = vx;
	this->vy = vy;
}
void Moveable::GetV(int *vx, int *vy)
{
	*vx = this->vx;
	*vy = this->vy;
}
void Moveable::SetD(int dirx, int diry)
{
	this->dirx = dirx;
	this->diry = diry;
}
void Moveable::GetD(int *dirx, int *diry)
{
	*dirx = this->dirx;
	*diry = this->diry;
}

void Character::ChangeHp(int hp){this->hp += hp;}
void Character::Kill(){this->hp = 0;}
bool Character::IsAlive(){return this->alive;}
int  Character::Weapon(){return this->weapon;}
void Character::Attack(int who)
{
	int t = time(NULL);
	int dirx,diry,x1,x2,y1,y2;
	this->GetD(&dirx,&diry);
	this->GetPos(&x1,&y1,&x2,&y2);
	Projectile pom = Projectile(dmgpocisku,zasiegpocisku,who);
	pom.SetD(dirx,diry);
	pom.SetPos(dirx>0?x2:x1, (y1+y2)/2);
	pom.SetSize(rozmiatpocisku,rozmiatpocisku);

	if(this->weapon == 1 && t-this->lastshot >= limitbroni1)
	{
		this->lastshot = t;
		pom.SetV(dirx*predkoscpocisku,0);
		P.push_back(pom);
	}
	if(this->weapon == 2 && t-this->lastshot >= limitbroni2)
	{
		this->lastshot = t;
		pom.SetV(dirx*predkoscpocisku,0);
		P.push_back(pom);

	}
	if(this->weapon == 3 && t-this->lastshot >= limitbroni3)
	{
		this->lastshot = t;
		pom.SetV(dirx*predkoscpocisku,0);
		P.push_back(pom);
	}
}
void Character::Jump()
{
	int vx,vy;
	this->GetV(&vx,&vy);
	if(vy == 0)this->SetV(vx,predkoscskoku);
}
void Character::Move()
{
	int x1,y1,x2,y2,vx,vy,dirx,diry;
	int a1,b1,a2,b2,p;
	this->GetPos(&x1,&y1,&x2,&y2);
	this->GetV(&vx,&vy);
	this->GetD(&dirx,&diry);

	bool kolizja = false;
	if(vy != 0)
	{
		for(int i=0;i<SO.size() && !kolizja;i++)
		{
			SO[i].GetPos(&a1,&b1,&a2,&b2);
			if(Collide(x1,y1+vy,x2,y2+vy,a1,b1,a2,b2))
			{
				kolizja = true;
				p = vy>0?1:-1;
				while(!Collide(x1,y1+p,x2,y2+p,a1,b1,a2,b2)){y1+=p;y2+=p;}
				vy = 0;
			}
		}
		if(kolizja == false){y1+=vy;y2+=vy;}
	}

	kolizja = false;
	if(vx != 0)
	{
		for(int i=0;i<SO.size() && !kolizja;i++)
		{
			SO[i].GetPos(&a1,&b1,&a2,&b2);
			if(Collide(x1+vx,y1,x2+vx,y2,a1,b1,a2,b2))
			{
				kolizja = true;
				p = vx>0?1:-1;
				while(!Collide(x1+1,y1,x2+1,y2,a1,b1,a2,b2)){x1+=p;x2+=p;}
			}
		}
		if(kolizja == false){x1+=vx;x2+=vx;}
	}

	this->SetPos(x1,y1,x2,y2);
	this->SetV(vx,vy);
}

Projectile::Projectile(int d,int r,int who)
{
	this->dmg = d;
	this->range = r;
	this->player = who;
}
bool Projectile::BOOM()
{
	int x1,x2,y1,y2;
	int a1,a2,b1,b2;
	this->GetPos(&x1,&y1,&x2,&y2);

	Hero.GetPos(&a1,&b1,&a2,&b2);
	if(!(this->player) && Collide(x1,y1,x2,y2,a1,b1,a2,b2))
	{
		Hero.ChangeHp(-1*(this->dmg));
		return true;
	}
	
	for(int i=0;i<E.size();i++)
	{
		E[i].GetPos(&a1,&b1,&a2,&b2);
		if((this->player) && Collide(x1,y1,x2,y2,a1,b1,a2,b2))
		{
			E[i].ChangeHp(-1*(this->dmg));
			return true;
		}
	}

	for(int i=0;i<SO.size();i++)
	{
		SO[i].GetPos(&a1,&b1,&a2,&b2);
		if(Collide(x1,y1,x2,y2,a1,b1,a2,b2))return true;
	}
return false;
}
void Projectile::Move()
{
	int vx,vy,x,y;
	this->GetPos(&x,&y);
	this->GetV(&vx,&vy);
	this->SetPos(x + vx,y + vy);
	this->range--;
}
void Projectile::Remove()
{
	//destruktory tekstur i jakies takie inne smieszne
}
int Projectile::Range(){return this->range;}

void Player::Action()
{
	int vx,vy;
	Hero.GetV(&vx,&vy);
	//wcisnieta strzalka do gory -> Hero.Jump();
	//wcisniete strzalki w bok Hero.SetV(predkosc ruchu * strona,vy)
	//wcisnieta spacja Hero.Attack(1);
}
void Player::Knife()
{
	//najchetniej bym wyjebał
}

void AICharacter::AI()
{

}
void AICharacter::Patrol()
{

}
