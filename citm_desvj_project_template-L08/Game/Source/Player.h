#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Physics.h"
#include "Window.h"
#include "Animation.h"
struct SDL_Texture;

class Player : public Entity
{
public:

	Player();
	
	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
	void OnCollision(PhysBody* physA, PhysBody* physB);
	

public:
	int doublejump;
	bool bandera;
	int salt = 0;
	int saltvel = -4;
	int deathtimer = 0;
	bool deathbool;
	bool dreta;
	int doublejumptimer;
	int menutimer;
	int atactimer;
	int lifes;
	int hitimer;
	bool idle;
	float xm;
	float ym;
	b2Vec2 vel = b2Vec2(0, 0);
	b2Vec2 death = b2Vec2(2, 1);
	float32 deathangle = 0;
private:

	//L02: DONE 1: Declare player parameters
	SDL_Texture* menutexture;
	SDL_Texture* menutexture2;
	SDL_Texture* texture;
	SDL_Texture* textureleft;
	SDL_Texture* playerdeadtext;
	SDL_Texture* deathtexture;
	SDL_Texture* closechest;
	SDL_Texture* openchest;
	SDL_Texture* congrats;
	SDL_Texture* doublejumptext;
	SDL_Texture* bluegemroll;


	Animation playeridleright;
	Animation playeridleleft;
	Animation playerrunright;
	Animation playerrunleft;
	Animation playerjumpright;
	Animation playerjumpleft;
	Animation playerdeathright;
	Animation playerdeathleft;
	Animation bluegem;
	Animation atacD;
	Animation atacE;


	SDL_Rect rect;
	SDL_Rect gemrect;
	SDL_Rect atacanim;

	const char* texturePath;

	// L07 DONE 5: Add physics to the player - declare a Physics body
	PhysBody* espasa;
	PhysBody* pbody;
	bool start;
	bool chest;
	int deathsound;
	int checkpointsound;
	int startsound;
	int chestopen;
	int espasasoroll;
	int jumpfx;
	int winsongfx;
	int hitsfx;
	iPoint gempos;

};

#endif // __PLAYER_H__