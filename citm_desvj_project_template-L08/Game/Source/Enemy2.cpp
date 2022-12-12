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
#include "Player.h"
#include "Pathfinding.h"
#include "Entity.h"
#include "Map.h"
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
	seashellidle.speed = 0.15f;

	seashelldie.PushBack({ 0,199,24,36 });
	seashelldie.PushBack({ 24,199,24,36 });
	seashelldie.PushBack({ 48,199,24,36 });
	seashelldie.PushBack({ 72,199,24,36 });
	seashelldie.loop = false;
	seashelldie.speed = 0.13f;
}

Enemy2::~Enemy2() {}

bool Enemy2::Awake() {


	return true;
}

bool Enemy2::Start() {

	texture = app->tex->Load("Assets/Textures/Spritesheets/Seashell.png");
	mouseTileTex = app->tex->Load("Assets/Textures/path_square.png");

	ebody = app->physics->CreateCircle(position.x + 16, position.y + 16, 12, bodyType::DYNAMIC);;
	initialpos = { PIXEL_TO_METERS((position.x + 10)),PIXEL_TO_METERS((position.y + 16)) };
	lastPathEnemy1 = NULL;
	isdead = false;
	vel = { 0,0 };
	deathtimer = 0;
	dreta = false;
	ebody->ctype = ColliderType::ENEMY;
	ebody->listener = this;
	isdead = false;
	view = false;
	return true;
}

bool Enemy2::Update()
{

	if (isdead == false) {

		if (deathtimer < 0) {
			pos = app->map->WorldToMap(METERS_TO_PIXELS(ebody->body->GetPosition().x), METERS_TO_PIXELS(ebody->body->GetPosition().y));
			playerpos = app->map->WorldToMap(METERS_TO_PIXELS(app->scene->player->GetPos().x), METERS_TO_PIXELS(app->scene->player->GetPos().y));
			if (playerpos.x < pos.x) {
				dreta = false;
			}
			if (playerpos.x > pos.x) {
				dreta = true;
			}
			if ((playerpos.x - pos.x) > -12 || view == true) {
				view = true;
				lenght = app->pathfinding->CreatePath(playerpos, pos);
				if (lenght > 1) {

					lastPathEnemy1 = app->pathfinding->GetLastPath();
					if (app->physics->debug == true) {
						for (uint i = 0; i < lastPathEnemy1->Count(); ++i)
						{
							iPoint pos = app->map->MapToWorld(lastPathEnemy1->At(i)->x, lastPathEnemy1->At(i)->y);
							app->render->DrawTexture(mouseTileTex, pos.x, pos.y);
						}
					}
					nextpos = lastPathEnemy1->At(lenght - 2);
					pos.x = nextpos->x - pos.x;
					pos.y = nextpos->y - pos.y;
					if (pos.x > 0) {
						vel.x = 1;

					}
					if (pos.x < 0) {
						vel.x = -1;

					}
					if (pos.y > 0) {
						vel.y = 1;

					}
					if (pos.y < 0) {
						vel.y = -1;

					}

				}
			}
			if (vel.x == 0) {
				seashell = seashellidle.GetCurrentFrame();
				seashellidle.Update();

			}
			if (vel.x == -1) {
				seashell = seashellidle.GetCurrentFrame();
				seashellidle.Update();

			}
			if (vel.x == 1) {
				seashell = seashellidle.GetCurrentFrame();
				seashellidle.Update();

			}
			if (dreta == true) {

				app->render->DrawFlipTexture(texture, METERS_TO_PIXELS(ebody->body->GetPosition().x) - 28, METERS_TO_PIXELS(ebody->body->GetPosition().y) - 26, &seashell);

			}
			if (dreta == false) {

				app->render->DrawTexture(texture, METERS_TO_PIXELS(ebody->body->GetPosition().x) - 28, METERS_TO_PIXELS(ebody->body->GetPosition().y) - 26, &seashell);

			}
		}
		if (deathtimer > 0) {
			
			seashell = seashelldie.GetCurrentFrame();
			seashelldie.Update();
			if (dreta == true) {

				app->render->DrawFlipTexture(texture, METERS_TO_PIXELS(ebody->body->GetPosition().x) - 15, METERS_TO_PIXELS(ebody->body->GetPosition().y) - 16, &seashell);

			}
			if (dreta == false) {

				app->render->DrawTexture(texture, METERS_TO_PIXELS(ebody->body->GetPosition().x) - 15, METERS_TO_PIXELS(ebody->body->GetPosition().y) - 16, &seashell);

			}
		}



	}
	if (isdead == true) {
		ebody->body->SetTransform({ -100,-100 }, 0);
	}
	if (app->scene->player->deathtimer > 0 && app->scene->player->deathtimer < 90) {
		isdead = false;
		seashelldie.Reset();
		view = false;
		ebody->body->SetActive(true);
		ebody->body->SetTransform(initialpos, 0);

	}


	ebody->body->SetLinearVelocity(vel);
	deathtimer--;
	if (deathtimer == 0) {
		isdead = true;
	}

	return true;
}

bool Enemy2::CleanUp()
{
	return true;
}

void Enemy2::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::ESPASA:

		ebody->body->SetActive(false);
		deathtimer = 50;

		break;

	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");

		break;

	default:

		break;
	}

}