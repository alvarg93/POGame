#include<SDL.h>


//Player Hero;
//vector <StaticObject> SO;
//vector <AICharacter> E;
//vector <Projectile> P;

void Engine();

class VisibleObject{
private:
        int x,y,w,h,texture;
public:
		VisibleObject();
		VisibleObject(int x, int y, int w, int h, int texture);
		int Texture(int text);
        void SetPos(int x,int y);
        void SetPos(int x1,int y1, int x2, int y2); 
        void GetPos(int *x,int *y);
        void GetPos(int *x1, int *y1, int *x2, int *y2);
		SDL_Rect Measures();
        void SetSize(int w,int h);
        void Display(SDL_Renderer *renderer, SDL_Texture **textures);
};

class StaticObject:public VisibleObject{
private:
        int type;
        void SetType(int t);
        void GetType(int *t);
public:
		StaticObject();
		StaticObject(int x,int y,int w, int h, int texture);
};

class Moveable:public VisibleObject{
private:
        int vx,vy,dirx,diry;
public:
//        void Animate();
        void GetV(int *vx,int *vy);
        void SetV(int vx,int vy);
        void GetD(int *dirx, int *diry);
        void SetD(int dirx, int diry);
        void Move();
};

class Character:public Moveable{
private:
        int hp,lastshot,weapon;
        bool alive;

public:
        void ChangeHp(int hp);
        void Kill();
        bool IsAlive();
        int  Weapon();
        void Attack(int who);
        void Jump();
        void Move();
};

class Projectile:public Moveable{
private:
        int dmg,range;
        bool player;

        void Remove();
public:
        Projectile(int d,int r,int who);
        int Range();
        bool BOOM();
        void Move();
};

class Player:public Character{
private:
        void Knife();
public:
        void Action();
};

class AICharacter:public Character{
private:
        void Patrol();
public:
        void AI();
};
