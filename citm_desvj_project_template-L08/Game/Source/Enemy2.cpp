#include "Enemy2.h"
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
Enemy2::Enemy2() : Entity(EntityType::ENEMY2)
{
	
}

Enemy2::~Enemy2() {}

bool Enemy2::Awake() {


	return true;
}

bool Enemy2::Start() {


	return true;
}

bool Enemy2::Update()
{

	return true;
}

bool Enemy2::CleanUp()
{
	return true;
}

void Enemy2::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");

		break;


	}

}