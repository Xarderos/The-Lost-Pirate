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
	
	name.Create("Enemy2");

	seashellidle.PushBack({ 0,152,48,38 });
	seashellidle.PushBack({ 48,152,48,38 });
	seashellidle.PushBack({ 96,152,48,38 });
	seashellidle.PushBack({ 144,152,48,38 });
	seashellidle.PushBack({ 192,152,48,38 });
	seashellidle.PushBack({ 240,152,48,38 });
	seashellidle.loop = true;
	seashellidle.speed = 0.13f;

}

Enemy2::~Enemy2() {}

bool Enemy2::Awake() {


	return true;
}

bool Enemy2::Start() {

	texture = app->tex->Load("Assets/Textures/Spritesheets/Seashell.png");

	ebody = app->physics->CreateRectangleSensor(position.x + 15, position.y + 24, 25, 20, bodyType::STATIC);
	ebody->ctype = ColliderType::DEATH;
	ebody->listener = this;

	return true;
}

bool Enemy2::Update()
{

	seashell = seashellidle.GetCurrentFrame();
	seashellidle.Update();
	app->render->DrawTexture(texture, position.x - 12, position.y - 3, &seashell);

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