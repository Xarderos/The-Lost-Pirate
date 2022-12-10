#ifndef __ENEMY1_H__
#define __ENEMY1_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Physics.h"
#include "Animation.h"

struct SDL_Texture;

class Enemy1 : public Entity
{
public:

	Enemy1();
	virtual ~Enemy1();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

public:
	PhysBody* ebody;
	Animation crabidle;
	Animation crabrun;
	Animation crabjump;
	Animation crabfall;
	Animation crabground;
	Animation crabanticipation;
	Animation crabattack;
	Animation crabhit;
	Animation crabdeadhit;
	Animation crabdeadground;
	SDL_Rect cranc;
	b2Vec2 vel;
	bool isdead;
	int crabdiefx;
	int deathtimer;
private:
	
	SDL_Texture* texture;
	const char* texturePath;

};

#endif // __ITEM_H__