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
#include "Player.h"
Enemy1::Enemy1() : Entity(EntityType::ENEMY1)
{
	name.Create("Enemy1");

	crabidle.PushBack({ 0,0,72,32 });
	crabidle.PushBack({ 72,0,72,32 });
	crabidle.PushBack({ 144,0,72,32 });
	crabidle.PushBack({ 216,0,72,32 });
	crabidle.PushBack({ 288,0,72,32 });
	crabidle.PushBack({ 360,0,72,32 });
	crabidle.PushBack({ 432,0,72,32 });
	crabidle.PushBack({ 504,0,72,32 });
	crabidle.PushBack({ 576,0,72,32 });
	crabidle.loop = true;
	crabidle.speed = 0.2f;

	crabrun.PushBack({ 0,32,72,32 });
	crabrun.PushBack({ 72,32,72,32 });
	crabrun.PushBack({ 144,32,72,32 });
	crabrun.PushBack({ 216,32,72,32 });
	crabrun.PushBack({ 288,32,72,32 });
	crabrun.PushBack({ 360,32,72,32 });
	crabrun.loop = true;
	crabrun.speed = 0.2f;

	crabjump.PushBack({ 0,64,72,32 });
	crabjump.PushBack({ 72,64,72,32 });
	crabjump.PushBack({ 144,64,72,32 });
	crabjump.loop = true;
	crabjump.speed = 0.2f;

	crabfall.PushBack({ 0,96,72,32 });
	crabfall.loop = true;
	crabfall.speed = 0.2f;

	crabground.PushBack({ 0,128,72,32 });
	crabground.PushBack({ 72,128,72,32 });
	crabground.loop = true;
	crabground.speed = 0.2f;

	crabattack.PushBack({ 0,192,72,32 });
	crabattack.PushBack({ 72,192,72,32 });
	crabattack.PushBack({ 144,192,72,32 });
	crabattack.PushBack({ 216,192,72,32 });
	crabattack.loop = true;
	crabattack.speed = 0.2f;

	crabhit.PushBack({ 0,224,72,32 });
	crabhit.PushBack({ 72,224,72,32 });
	crabhit.PushBack({ 144,224,72,32 });
	crabhit.PushBack({ 216,224,72,32 });
	crabhit.loop = true;
	crabhit.speed = 0.2f;

	crabdeadhit.PushBack({ 0,256,72,32 });
	crabdeadhit.PushBack({ 72,256,72,32 });
	crabdeadhit.PushBack({ 144,256,72,32 });
	crabdeadhit.PushBack({ 216,256,72,32 });
	crabdeadhit.loop = true;
	crabdeadhit.speed = 0.2f;

	crabdeadground.PushBack({ 0,288,72,32 });
	crabdeadground.PushBack({ 72,288,72,32 });
	crabdeadground.PushBack({ 144,288,72,32 });
	crabdeadground.PushBack({ 216,288,72,32 });
	crabdeadground.loop = true;
	crabdeadground.speed = 0.2f;

}

Enemy1::~Enemy1() {}

bool Enemy1::Awake() {


	return true;
}

bool Enemy1::Start() {

	texture = app->tex->Load("Assets/Textures/Spritesheets/Crab.png");

	ebody = app->physics->CreateRectangle(position.x + 15, position.y + 24, 20, 15, bodyType::DYNAMIC);
	ebody->listener = this;
	ebody->ctype = ColliderType::ENEMY;
	isdead = false;
	return true;
}

bool Enemy1::Update()
{
	if (isdead == false) {
		cranc = crabidle.GetCurrentFrame();
		crabidle.Update();
		app->render->DrawTexture(texture, METERS_TO_PIXELS(ebody->body->GetPosition().x)-36, METERS_TO_PIXELS(ebody->body->GetPosition().y)-20, &cranc);
	}
	if (isdead == true) {
		ebody->body->SetTransform({ -100,-100 }, 0);
	}


	return true;
}

bool Enemy1::CleanUp()
{
	return true;
}

void Enemy1::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{

	case ColliderType::ESPASA:

		isdead = true;

		break;

	case ColliderType::UNKNOWN:

		LOG("Collision UNKNOWN");

		break;

	default:

		break;

	}

}