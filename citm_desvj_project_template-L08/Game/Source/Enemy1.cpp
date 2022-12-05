#include "Enemy1.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Animation.h"
Enemy1::Enemy1() : Entity(EntityType::ENEMY1)
{
	
}

Enemy1::~Enemy1() {}

bool Enemy1::Awake() {


	return true;
}

bool Enemy1::Start() {


	return true;
}

bool Enemy1::Update()
{

	return true;
}

bool Enemy1::CleanUp()
{
	return true;
}

void Enemy1::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");

		break;


	}

}