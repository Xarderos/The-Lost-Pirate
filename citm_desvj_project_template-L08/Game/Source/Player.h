#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Physics.h"
#include "Window.h"
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
	int saltvel = -5;
	int deathtimer = 0;
	bool deathbool;
	bool dreta;
	int doublejumptimer;
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

	const char* texturePath;

	// L07 DONE 5: Add physics to the player - declare a Physics body
	PhysBody* pbody;
	bool start;
	bool chest;
	int pickCoinFxId;
	int deathsound;
	int checkpointsound;
	int startsound;
	int menutimer;
};

#endif // __PLAYER_H__