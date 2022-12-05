#ifndef __ENEMY2_H__
#define __ENEMY2_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Physics.h"
#include "Animation.h"

struct SDL_Texture;

class Enemy2 : public Entity
{
public:

	Enemy2();
	virtual ~Enemy2();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

public:

	
private:
	
	SDL_Texture* texture;
	const char* texturePath;

};

#endif // __ITEM_H__