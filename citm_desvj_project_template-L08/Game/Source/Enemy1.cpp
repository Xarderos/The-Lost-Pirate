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
	name.Create("Enemy1");

	crab.PushBack({ 0,0,72,32 });
	crab.PushBack({ 72,0,72,32 });
	crab.PushBack({ 144,0,72,32 });
	crab.PushBack({ 216,0,72,32 });
	crab.PushBack({ 288,0,72,32 });
	crab.PushBack({ 360,0,72,32 });
	crab.PushBack({ 432,0,72,32 });
	crab.PushBack({ 504,0,72,32 });
	crab.PushBack({ 576,0,72,32 });
	crab.loop = true;
	crab.speed = 0.2f;
}

Enemy1::~Enemy1() {}

bool Enemy1::Awake() {


	return true;
}

bool Enemy1::Start() {

	texture = app->tex->Load("Assets/Textures/Spritesheets/Crab.png");

	ebody = app->physics->CreateRectangleSensor(position.x + 15, position.y + 24, 20, 15, bodyType::STATIC);
	ebody->ctype = ColliderType::DEATH;
	ebody->listener = this;

	return true;
}

bool Enemy1::Update()
{

	cranc = crab.GetCurrentFrame();
	crab.Update();
	app->render->DrawTexture(texture, position.x - 23, position.y + 4, &cranc);

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