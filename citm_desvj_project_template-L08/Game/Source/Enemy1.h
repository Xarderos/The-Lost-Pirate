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
	Animation crab;
	SDL_Rect cranc;
private:
	
	SDL_Texture* texture;
	const char* texturePath;

};

#endif // __ITEM_H__